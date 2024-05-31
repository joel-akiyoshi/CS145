/*
 * voltmeter.h
 *
 * Created: 5/24/2024 3:42:20 PM
 *  Author: Chan Young Ji & Joel Akiyoshi
 */ 

#ifndef _VOLTMETER_H
#define _VOLTMETER_H

int get_sample(void);

unsigned int compute_max(unsigned int current_max);

unsigned int compute_min(unsigned int current_min);

#endif /* _VOLTMETER_H */
