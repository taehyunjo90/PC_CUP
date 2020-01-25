#ifndef CYBER_SPACESHIP_H
#define CYBER_SPACESHIP_H

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length);

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count);

/* my func */
int is_safe_area(size_t current_location_cluster_count);
int is_cluster(char* current_check_location, const char* const cluster_start_location, const size_t clutser_lengh);
char* get_cluster_end_address(const char* const cluster_start_location, const size_t cluster_length);

#endif /* CYBER_SPACESHIP */
