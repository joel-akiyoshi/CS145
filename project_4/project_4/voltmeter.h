/*
 * voltmeter.h
 *
 * Created: 5/24/2024 3:42:20 PM
 *  Author: Chan Young Ji & Joel Akiyoshi
 */ 

#ifndef _VOLTMETER_H
#define _VOLTMETER_H

int get_sample(void);

int compute_max(int current_max);

int compute_min(int current_min);

int compute_avg(int current_avg);

#endif /* _VOLTMETER_H */
