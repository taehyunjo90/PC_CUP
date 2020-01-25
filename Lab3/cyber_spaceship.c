#include "cyber_spaceship.h"
#include <stdio.h>

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
    size_t idx;
    size_t i;
    
    char* max_safe_area_start_location;
    size_t max_safe_area_length = 0;
    
    char* current_safe_area_start_location;
    size_t current_safe_area_length;
    int is_before_location_safe = 0;
    int is_current_location_safe;
    
    char* current_check_location;
    size_t current_location_cluster_count;
    
    if (cab_length == 0) {
        *out_longest_safe_area_length = 0;
        return NULL;
    }
    
    
    for (idx = 0; idx < cab_length; ++idx) {
        current_check_location = (char*)(cab_start_location + idx);
        current_location_cluster_count = 0;
        for (i = 0; i < cluster_count; ++i) {
            current_location_cluster_count += is_cluster(current_check_location, cluster_start_locations[i], cluster_lengths[i]);
        }
        
        is_current_location_safe = is_safe_area(current_location_cluster_count);
        
        if (is_before_location_safe == 0 && is_current_location_safe == 1){
            current_safe_area_start_location = current_check_location;
            current_safe_area_length = 1;
        } else if (is_before_location_safe == 1 && is_current_location_safe == 1) {
            current_safe_area_length += 1;
        }
        
        if (current_safe_area_length > max_safe_area_length) {
            max_safe_area_start_location = current_safe_area_start_location;
            max_safe_area_length = current_safe_area_length;
        }
        
        is_before_location_safe = is_current_location_safe;
        
        /* printf("@idx:%d %p, cluster counts:%d -> is safe area : %d, safe_length : %d\n", idx, (void*)current_check_location, current_location_cluster_count, is_safe_area(current_location_cluster_count), current_safe_area_length); */
        /* printf("max safe start location : %p, max_safe_area_length : %d\n", (void*)max_safe_area_start_location, max_safe_area_length); */
    }
    
    *out_longest_safe_area_length = max_safe_area_length;
    return max_safe_area_start_location;
}

int is_safe_area(size_t current_location_cluster_count)
{
    if (current_location_cluster_count % 2 == 0) {
        return 1;
    }
    return 0;
}

int is_cluster(char* current_check_location, const char* const cluster_start_location, const size_t clutser_lengh)
{
    char* cluster_end_location = get_cluster_end_address(cluster_start_location, clutser_lengh);
    if (current_check_location >= cluster_start_location && current_check_location <= cluster_end_location) {
        return 1;
    }
    return 0;
}

char* get_cluster_end_address(const char* const cluster_start_location, const size_t cluster_length)
{
    return (char*)cluster_start_location + cluster_length - 1;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
    size_t idx;
    size_t i;
    
    int is_current_location_safe;
    int current_location_cluster_count;
    char* current_check_location;
    
    double travel_time = 0;
        
    for (idx = 0; idx < cab_length; ++idx) {
        current_check_location = (char*)(cab_start_location + idx);
        current_location_cluster_count = 0;
        for (i = 0; i < cluster_count; ++i) {
            current_location_cluster_count += is_cluster(current_check_location, cluster_start_locations[i], cluster_lengths[i]);
        }
        
        is_current_location_safe = is_safe_area(current_location_cluster_count);
        
        if (is_current_location_safe == 1) {
            travel_time += 0.1;
        } else if (is_current_location_safe == 0) {
            travel_time += 0.2;
        }
    }
    
    /* printf("travel time : %f", travel_time); */
    return (int) (travel_time + 0.5);
}
