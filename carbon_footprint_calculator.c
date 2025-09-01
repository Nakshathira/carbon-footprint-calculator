#include <stdio.h>
#include <string.h>
// National per-person averages (India, annualized)
const float AVG_ELEC   = 1395.0;  // kWh
const float AVG_PETROL = 26.78;   // L
const float AVG_DIESEL = 63.0;    // L   <- Corrected
const float AVG_LPG    = 20.36;   // kg
const float AVG_AIR    = 110.0;   // passenger-km
const float AVG_RAIL   = 825.0;   // passenger-km
const float AVG_BIOM   = 423.0;   // kg

/* Emission factors (kg CO₂ per unit) */
const float EF_ELEC   = 0.727;
const float EF_PETROL = 2.271;
const float EF_DIESEL = 2.6444;
const float EF_LPG    = 2.6;
const float EF_WASTE  = 0.005;
const float EF_AIR    = 0.24;
const float EF_RAIL   = 0.0115;
const float EF_BIOM   = 2.5;

/* National average total emissions (tonnes CO₂ per person per year) */
const float NATIONAL_AVG_T = 2.84;

int main() {
    float m_elec, m_petrol, m_diesel, m_lpg;
    float m_waste, m_air_km, m_rail_km, m_biomass;
    char name[50];
    FILE *final = fopen("Carbonfootprintreport.csv", "a+");
    long size = ftell(final);
    if (size == 0)
    {
        fprintf(final,"Name,Electricity(kWh),Petrol(L),Diesel(L),LPG(L),Waste(kg),Air(km),Rail(km),Biomass(kg),Total CO2\n");
    }
    printf("Enter your name ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; 
    printf("Enter your average MONTHLY consumption for each category:\n");
    printf("Electricity (kWh): ");     scanf("%f", &m_elec);if (m_elec < 0) m_elec = -m_elec;
    printf("Petrol (L): ");            scanf("%f", &m_petrol);if (m_petrol < 0) m_petrol = -m_petrol;
    printf("Diesel (L): ");            scanf("%f", &m_diesel);if (m_diesel < 0) m_diesel = -m_diesel;
    printf("LPG (L): ");               scanf("%f", &m_lpg);if (m_lpg < 0) m_lpg = -m_lpg;
    printf("Air travel (km): ");  scanf("%f", &m_air_km);if (m_air_km < 0) m_air_km = -m_air_km;
    printf("Rail travel (km): "); scanf("%f", &m_rail_km);if (m_rail_km < 0) m_rail_km = -m_rail_km;
    printf("Biomass (kg): ");          scanf("%f", &m_biomass);if (m_biomass < 0) m_biomass = -m_biomass;

    /* Annualize usage */
    float a_elec   = m_elec   * 12.0;
    float a_petrol = m_petrol * 12.0;
    float a_diesel = m_diesel * 12.0;
    float a_lpg    = m_lpg    * 12.0;
    float a_air    = m_air_km * 12.0;
    float a_rail   = m_rail_km* 12.0;
    float a_biom   = m_biomass* 12.0;

    /* Compute diff ratios compared to average */
    float diff_elec   = (a_elec   - AVG_ELEC)   / AVG_ELEC;
    float diff_petrol = (a_petrol - AVG_PETROL) / AVG_PETROL;
    float diff_diesel = (a_diesel - AVG_DIESEL) / AVG_DIESEL;
    float diff_lpg    = (a_lpg    - AVG_LPG)    / AVG_LPG;
    float diff_air    = (a_air    - AVG_AIR)    / AVG_AIR;
    float diff_rail   = (a_rail   - AVG_RAIL)   / AVG_RAIL;
    float diff_biom   = (a_biom   - AVG_BIOM)   / AVG_BIOM;

    /* Calculate annual emissions (kg CO₂) */
    float kg_elec   = a_elec   * EF_ELEC;
    float kg_petrol = a_petrol * EF_PETROL;
    float kg_diesel = a_diesel * EF_DIESEL;
    float kg_lpg    = a_lpg    * EF_LPG;
    float kg_air    = a_air    * EF_AIR;
    float kg_rail   = a_rail   * EF_RAIL;
    float kg_biom   = a_biom   * EF_BIOM;

    float total_kg = kg_elec + kg_petrol + kg_diesel
                   + kg_lpg + kg_air
                   + kg_rail + kg_biom;
    float total_t  = total_kg / 1000.0f;

    /* Output */
    printf("\nYour Annual Usage vs National Avg:\n\n");

printf("Electricity:   You = %.2f kWh, National = %.2f kWh\n",
       a_elec, AVG_ELEC);

printf("Petrol:        You = %.2f L,   National = %.2f L\n",
       a_petrol, AVG_PETROL);

printf("Diesel:        You = %.2f L,   National = %.2f L\n",
       a_diesel, AVG_DIESEL);

printf("LPG:           You = %.2f L,   National = %.2f L\n",
       a_lpg, AVG_LPG);



printf("Air travel:    You = %.2f km,  National = %.2f km\n",
       a_air, AVG_AIR);

printf("Rail travel:   You = %.2f km,  National = %.2f km\n",
       a_rail, AVG_RAIL);

printf("Biomass:       You = %.2f kg,  National = %.2f kg\n",
       a_biom, AVG_BIOM);
printf("\nyour average carbon footprint(in tonnes):%.2f",total_t);
printf("\nNational Avg Footprint: %.2f tonnes CO₂/year\n",
       NATIONAL_AVG_T);


    fprintf(final, "%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",name, a_elec, a_petrol, a_diesel, a_lpg,a_air, a_rail, a_biom, total_t, NATIONAL_AVG_T);
    fclose(final);

    /* Recommendations */
    printf("\n--- Recommendations (>%2.0f%% above avg) ---\n", 20.0f);
    if (diff_elec   > 0.20) printf("• Cut electricity by improving efficiency or using renewables.\n");
    if (diff_petrol > 0.20) printf("• Reduce petrol use: car-share, public transit, efficient driving.\n");
    if (diff_diesel > 0.20) printf("• Cut diesel use: rethink heavy vehicle trips or switch fuel.\n");
    if (diff_lpg    > 0.20) printf("• Optimize LPG cooking practices and check for leaks.\n");
    if (diff_air    > 0.20) printf("• Fly less: opt for virtual meetings.\n");
    if (diff_rail   > 0.20) printf("• decrease rail use for travel in place of higher-carbon modes.\n");
    if (diff_biom   > 0.20) printf("• Switch to cleaner cooking fuels or efficient stoves.\n");
    if (total_t > NATIONAL_AVG_T) {
        printf("Overall: Your footprint is above the national average; focus on the above areas.\n");
    } else {
        printf("Overall: Your footprint is below the national average—keep up the good work!\n");
    }

    return 0;
}
