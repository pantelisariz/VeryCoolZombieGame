// zombies_stella.cpp
// Translation of the provided Stella system dynamics model to C++ (Euler DT=1).
#include <fstream>
#include <iomanip>
#include <vector>
#include <iostream>
using namespace std;

struct Batch {
    double amount;     // people currently in conveyor (bitten & incubating)
    double remaining;  // days left before conversion
};

int main() {
    // ----- TIME SPECS -----
    const int STARTTIME = 0;
    const int STOPTIME  = 120;
    const double DT     = 1.0; // Euler, daily steps

    // ----- CONSTANTS / INITIALIZATION -----
    const double days_to_become_infected_from_bite = 15.0; // Days
    const double Bitten_Two_capacity = 100.0;              // People (capacity inside conveyor)
    const double patient_zero = 1.0;                       // Zombies
    const double CONVERSION_FROM_PEOPLE_TO_ZOMBIES = 1.0;  // Zombies/People
    const double normal_number_of_bites = 1.0;             // People/zombie/day
    const double land_area = 1000.0;                       // m2
    const double normal_population_density = 0.1;          // people/m2

    // Stocks (initial)
    double Susceptible = 100.0;        // People (called Zombies in the text, but used as People)
    double Zombies = patient_zero;     // Zombies
    // Conveyor content is the stock "Bitten_Two" (people incubating):
    vector<Batch> conveyor;            // accepts multiple batches
    auto conveyor_content = [&](){
        double sum = 0.0;
        for (auto &b : conveyor) sum += b.amount;
        return sum;
    };

    // GRAPH points: population_density_effect_on_zombie_bites
    // x = population_density / normal_population_density
    const vector<pair<double,double>> graphPts = {
        {0.000, 0.014}, {0.200, 0.041}, {0.400, 0.101}, {0.600, 0.189}, {0.800, 0.433},
        {1.000, 1.000}, {1.200, 1.217}, {1.400, 1.282}, {1.600, 1.300}, {1.800, 1.300},
        {2.000, 1.300}
    };
    auto graph_lookup = [&](double x)->double {
        // Piecewise linear interpolation with endpoint clamping
        if (x <= graphPts.front().first) return graphPts.front().second;
        if (x >= graphPts.back().first)  return graphPts.back().second;
        for (size_t i = 1; i < graphPts.size(); ++i) {
            if (x <= graphPts[i].first) {
                double x0 = graphPts[i-1].first, y0 = graphPts[i-1].second;
                double x1 = graphPts[i].first,   y1 = graphPts[i].second;
                double t = (x - x0) / (x1 - x0);
                return y0 + t*(y1 - y0);
            }
        }
        return graphPts.back().second; // fallback
    };

    // CSV output
    ofstream csv("zombies_output.csv");
    csv << "time,Susceptible,Bitten_Two,Zombies\n";
    auto write_row = [&](int t){
        csv << t << ","
            << fixed << setprecision(6)
            << Susceptible << ","
            << conveyor_content() << ","
            << Zombies << "\n";
    };

    // Write initial row at t=0
    write_row(0);

    // ----- SIMULATION LOOP -----
    for (int t = STARTTIME; t < STOPTIME; t += (int)DT) {
        // --- Calculate auxiliaries (using values at current time t) ---
        double Bitten_Two = conveyor_content(); // current conveyor content (people)
        double non_zombie_population = Bitten_Two + Susceptible; // People
        double population_density = non_zombie_population / land_area; // people/m2

        double x = population_density / normal_population_density; // dimensionless
        double population_density_effect_on_zombie_bites = graph_lookup(x);

        double number_of_bites_per_zombie_per_day =
            normal_number_of_bites * population_density_effect_on_zombie_bites; // People/zombie/day

        // ROUND as in Stella (nearest int, half away from zero) -> std::round
        double total_bitten_per_day =
            round(Zombies * number_of_bites_per_zombie_per_day); // People/day

        // Avoid division by zero by MAX(non_zombie_population, 1)
        double denom = max(non_zombie_population, 1.0);
        double number_of_bites_from_total_zombies_on_susceptible =
            round((Susceptible / denom) * total_bitten_per_day); // People/day

        // getting_bitten UNIFLOW, but enforce NON-NEGATIVE Susceptible
        double getting_bitten = number_of_bites_from_total_zombies_on_susceptible;
        // Truncate to not exceed available Susceptible this step (Euler non-negative safeguard)
        getting_bitten = min(getting_bitten, floor(Susceptible)); // ensure we don't drive below 0

        // --- Conveyor mechanics for Bitten_Two ---
        // 1) Progress existing batches and compute raw outflow (people exiting conveyor)
        double raw_outflow_people = 0.0;
        for (auto &b : conveyor) {
            b.remaining -= DT;
        }
        // collect finished batches
        vector<Batch> next_conveyor;
        next_conveyor.reserve(conveyor.size());
        for (auto &b : conveyor) {
            if (b.remaining <= 0.0) {
                raw_outflow_people += b.amount;
            } else {
                next_conveyor.push_back(b);
            }
        }
        conveyor.swap(next_conveyor);

        // 2) Capacity check for new inflow (people)
        double current_content = conveyor_content();
        double free_cap = max(0.0, Bitten_Two_capacity - current_content);
        double inflow_people = max(0.0, min(getting_bitten, free_cap));

        if (inflow_people > 0.0) {
            conveyor.push_back(Batch{inflow_people, days_to_become_infected_from_bite});
        }

        // 3) Conveyor outflow converted to zombies
        double becoming_infecting = raw_outflow_people * CONVERSION_FROM_PEOPLE_TO_ZOMBIES; // Zombies/day

        // --- STOCK UPDATES (Euler) ---
        // Susceptible(t+1) = S(t) - getting_bitten
        Susceptible = max(0.0, Susceptible - getting_bitten * DT);

        // Zombies(t+1) = Z(t) + becoming_infecting
        Zombies = max(0.0, Zombies + becoming_infecting * DT);

        // Bitten_Two stock is already handled implicitly by conveyor vector
        // (content increased by inflow_people, decreased by raw_outflow_people)

        // --- (Optional) derived integer populations, not used further ---
        // double Susceptible_Population = floor(Susceptible);
        // double Zombie_Population = floor(Zombies);

        // Write row for t+DT
        write_row(t + (int)DT);
    }

    csv.close();
    cout << "Simulation complete. Wrote zombies_output.csv\n";
    return 0;
}