/**
 *  -------------------------------------------
 *  -={ From the magic land of the Ker Nel! }=-
 *  -------------------------------------------
 *
 * This file was developed by Josh Thomas of Monkworks / Atredis (atredis.com) / @m0nk_dot on the twitterz
 *
 * Sole intent of this program:
 *	This program is a very simplistic PoC for timing based attestation checks on ARM CPUs
 *
 **/

//--------------------------------------------------------
// Standard Includes
//--------------------------------------------------------
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/cpufreq.h>
#include <linux/ktime.h>
#include <linux/hrtimer.h>
#include <linux/delay.h>


//--------------------------------------------------------
// Defines for "easy" config
//--------------------------------------------------------
#define ATTESTIFY_TEST_LOOP_COUNTER 		100
#define ATTESTIFY_PROCESS_LOOP_COUNTER 		100
#define ATTESTIFY_CALC_LOOP_COUNTER			10000

typedef enum {
	SHORT_TEST_MODE, 
	MEDIUM_TEST_MODE,
	LONG_TEST_MODE,
} ATTESTIFY_MODE;

#define XPERIA_Z_CORE_COUNT					4

// Just some simple return values
#define EPIC_FAIL							0
#define WOOT								1


//--------------------------------------------------------
// Retrieve system stats from kernel and runtime
//--------------------------------------------------------
static int kernel_extract_cpu_speed_info( void ) {
	int ret_val;
	int cpu_speeds[XPERIA_Z_CORE_COUNT];
	int i;

	/**
	 *	Currently in this section, CPU cores 1-3 report 0 for the speed... 
	 *	This is a failure of the frameworks we are using
	 *	
	 *	This is also an acceptable problem currently.  If the design of CLB
	 *	were to go into acutal production, this would need to be fixed,
	 *	but for the PoC, it is fine.
	 *
	 *	This would only be a problem if the offensive kit we are targeting
	 *	forced the code to run on a different core than the default, and
	 *	that functionality is beyond the scope of this research (though interesting)
	 *
	 */

	for(i = 0; i < XPERIA_Z_CORE_COUNT; i++) {
		cpu_speeds[i] = cpufreq_get(i);
 		
 		if(cpu_speeds[i] == 0)
 			cpu_speeds[i] = cpufreq_quick_get(i);
		
		if(cpu_speeds[i] == 0)
 			cpu_speeds[i] = cpufreq_quick_get_max(i);
		
		if(cpu_speeds[i] != 0)
			pr_info("\t[attestify] -> reported speed of CPU%d is: %d", i, cpu_speeds[i]);
	
	}
	
	//Set the return value to the current CPU0 speed
	ret_val = cpu_speeds[0];
	
	return ret_val;		//Upon success, ret_val will be a non-zero value
}

//--------------------------------------------------------
// Math returns!
//--------------------------------------------------------
static void collatz_sequence_processor( long seed ) {  
    
    //Small collatz calc with no frills
    while ( seed > 1 ){
        if( (seed % 2) != 0 ){
            seed = ((3 * seed) + 1);
        } else {
            seed = (seed / 2);
        }
    }
    return;
}

static void factorial_sequence_processor( unsigned long seed ) {
	unsigned long calculated_roller;

	while( seed > 0 )
	{
		calculated_roller = (seed * (seed - 1));
		seed -= seed;		
	}
	//This should roll some digits, but we don't care... just want the processor cycles.
}
//--------------------------------------------------------
// Run the Phase 0 test
//--------------------------------------------------------
static int phase_0_testing( ATTESTIFY_MODE test_scope ) {

	int ret_val;
	int i_outer, i_inner;
	ktime_t start_time;
	unsigned long tmp_val;
	
	unsigned long _scopes[ATTESTIFY_PROCESS_LOOP_COUNTER];
	unsigned long _mean;
	unsigned long _standard_deviation;
	unsigned long _deviation_percentage;
	
	ret_val 			= 	EPIC_FAIL;
	_mean 				= 	0;
	
	pr_info("[attestify] -> Phase 0 testing starting now...");
	
	switch(test_scope) {
		case SHORT_TEST_MODE:
		{
			//-----------------------
			// Run the short tests
			//-----------------------
			pr_info("[attestify] -> Phase 0 - Short tests:");
	
			//Run the short calculations (this just does some silly math, < 10 cycles per loop?)
			for (i_outer = 0; i_outer < ATTESTIFY_PROCESS_LOOP_COUNTER; i_outer++)
			{
				start_time = ktime_get();

				tmp_val = 10;

				for (i_inner = 0; i_inner < ATTESTIFY_CALC_LOOP_COUNTER; i_inner++)
				{
					tmp_val = ((tmp_val + 1) * (tmp_val -1)) / (ATTESTIFY_CALC_LOOP_COUNTER + 1);
				}
				
				_scopes[i_outer] = 0;	
				_scopes[i_outer] = ktime_us_delta(ktime_get(), start_time);
				_mean += _scopes[i_outer];

				//pr_info("[attestify] -> Phase 0 - Short - Run %d - Delta: %lu", i_outer, short_scopes[i_outer]);

				msleep(100);	
			}
			
			//-----------------------
			// Process the short tests
			//-----------------------
			_standard_deviation = 0;
			pr_info("[attestify] -> Phase 0 - Post Test Processing:");

			_mean = (_mean / ATTESTIFY_PROCESS_LOOP_COUNTER);
			pr_info("\t[attestify] -> Phase 0 - Short average time: %lu", _mean);	
	
			for (i_outer = 0; i_outer < ATTESTIFY_PROCESS_LOOP_COUNTER; i_outer++)
			{
				tmp_val = 0;
				tmp_val = abs(_scopes[i_outer] - _mean);
				_standard_deviation += (tmp_val * tmp_val);
			}
	
			tmp_val = (_standard_deviation / ATTESTIFY_PROCESS_LOOP_COUNTER);
			_standard_deviation = int_sqrt(tmp_val); 
			pr_info("\t[attestify] -> Phase 0 - Short Standard Deviation: %lu", _standard_deviation);
	
			_deviation_percentage = 0;
			if( _mean > 0 )
				_deviation_percentage = (_standard_deviation * 100) / _mean;
			pr_info("\t[attestify] -> Phase 0 - Short Deviation Int Percentage: %lu", _deviation_percentage);	

			break;
		}	
		
		case MEDIUM_TEST_MODE:
		{
			//-----------------------
			// Run the medium tests
			//-----------------------
			pr_info("[attestify] -> Phase 0 - Medium tests:");
	
			//Run the medium calculations (factorials!)
			for (i_outer = 0; i_outer < ATTESTIFY_PROCESS_LOOP_COUNTER; i_outer++)
			{
				start_time = ktime_get();

				tmp_val = 10;

				for (i_inner = 0; i_inner < ATTESTIFY_CALC_LOOP_COUNTER; i_inner++)
				{
					tmp_val--;
					if(tmp_val < 2)
						tmp_val = 10;
		 			factorial_sequence_processor(tmp_val);
				}
				
				_scopes[i_outer] = 0;	
				_scopes[i_outer] = ktime_us_delta(ktime_get(), start_time);
				_mean += _scopes[i_outer];

				//pr_info("[attestify] -> Phase 0 - Medium - Run %d - Delta: %lu", i_outer, short_scopes[i_outer]);

				msleep(100);	
			}
			
			//-----------------------
			// Process the Medium tests
			//-----------------------
			_standard_deviation = 0;
			pr_info("[attestify] -> Phase 0 - Post Test Processing:");

			_mean = (_mean / ATTESTIFY_PROCESS_LOOP_COUNTER);
			pr_info("\t[attestify] -> Phase 0 - Medium average time: %lu", _mean);	
	
			for (i_outer = 0; i_outer < ATTESTIFY_PROCESS_LOOP_COUNTER; i_outer++)
			{
				tmp_val = 0;
				tmp_val = abs(_scopes[i_outer] - _mean);
				_standard_deviation += (tmp_val * tmp_val);
			}
	
			tmp_val = (_standard_deviation / ATTESTIFY_PROCESS_LOOP_COUNTER);
			_standard_deviation = int_sqrt(tmp_val); 
			pr_info("\t[attestify] -> Phase 0 - Medium Standard Deviation: %lu", _standard_deviation);
	
			_deviation_percentage = 0;
			if( _mean > 0 )
				_deviation_percentage = (_standard_deviation * 100) / _mean;
			pr_info("\t[attestify] -> Phase 0 - Medium Deviation Int Percentage: %lu", _deviation_percentage);

			break;
		}
	
		case LONG_TEST_MODE:
		{
			//-----------------------
			// Run the Long tests
			//-----------------------
			pr_info("[attestify] -> Phase 0 - Long tests:");
	
			//Run the long calculations (collatz it up)
			for (i_outer = 0; i_outer < ATTESTIFY_PROCESS_LOOP_COUNTER; i_outer++)
			{
				start_time = ktime_get();

				tmp_val = 10;

				for (i_inner = 0; i_inner < ATTESTIFY_CALC_LOOP_COUNTER; i_inner++)
				{
		 			collatz_sequence_processor(tmp_val);
				}
				
				_scopes[i_outer] = 0;	
				_scopes[i_outer] = ktime_us_delta(ktime_get(), start_time);
				_mean += _scopes[i_outer];

				//pr_info("[attestify] -> Phase 0 - Long - Run %d - Delta: %lu", i_outer, short_scopes[i_outer]);

				msleep(100);	
			}
			
			//-----------------------
			// Process the Medium tests
			//-----------------------
			_standard_deviation = 0;
			pr_info("[attestify] -> Phase 0 - Post Test Processing:");

			_mean = (_mean / ATTESTIFY_PROCESS_LOOP_COUNTER);
			pr_info("\t[attestify] -> Phase 0 - Long average time: %lu", _mean);	
	
			for (i_outer = 0; i_outer < ATTESTIFY_PROCESS_LOOP_COUNTER; i_outer++)
			{
				tmp_val = 0;
				tmp_val = abs(_scopes[i_outer] - _mean);
				_standard_deviation += (tmp_val * tmp_val);
			}
	
			tmp_val = (_standard_deviation / ATTESTIFY_PROCESS_LOOP_COUNTER);
			_standard_deviation = int_sqrt(tmp_val); 
			pr_info("\t[attestify] -> Phase 0 - Long Standard Deviation: %lu", _standard_deviation);
	
			_deviation_percentage = 0;
			if( _mean > 0 )
				_deviation_percentage = (_standard_deviation * 100) / _mean;
			pr_info("\t[attestify] -> Phase 0 - Long Deviation Int Percentage: %lu", _deviation_percentage);

			break;
		}
	}
		
	msleep(100);

	return WOOT;
}

//--------------------------------------------------------
// Print processor info
//--------------------------------------------------------
static int print_info_about_processor( void ) {
	int ret_val;
	int core_zero_speed;
	
	ret_val 			= 	EPIC_FAIL;
	core_zero_speed		= 	EPIC_FAIL;
	
	msleep(100);

	//Get the runtime value of the CPU prior to starting the real test.
	pr_info("[attestify] -> CPU INFO - Attempting to obtain the CPU speeds");
	core_zero_speed = kernel_extract_cpu_speed_info();
	if( core_zero_speed == EPIC_FAIL )
		pr_info("[attestify] -> CPU INFO - Cannot obtain the actual CPU speed, failing quick");
	
	msleep(100);


	return ret_val;		//Upon success, ret_val will be a non-zero value
}


//--------------------------------------------------------
// Boring Module stuff
//--------------------------------------------------------

static int __init clb_attestify_init(void)
{
	int ret_val;
	int i;

	ret_val = EPIC_FAIL;

	pr_info("[attestify] -> loading the clb_attestify_init module");

	for (i = 0; i < ATTESTIFY_TEST_LOOP_COUNTER; i++)
	{
		pr_info("[attestify] -> Attestify test number %d of %d", i, (int)ATTESTIFY_TEST_LOOP_COUNTER);
		
		ret_val = print_info_about_processor();

		ret_val = phase_0_testing(SHORT_TEST_MODE);
		ret_val = phase_0_testing(MEDIUM_TEST_MODE);
		ret_val = phase_0_testing(LONG_TEST_MODE);
	}	
	
	// All processing is done, we can rmmod the module now (do this automatically?)
	return EPIC_FAIL;
}

static void __exit clb_attestify_exit(void)
{
	// Goodbye
	return;
}

module_init(clb_attestify_init);
module_exit(clb_attestify_exit);

MODULE_DESCRIPTION("PoC for runtime validation of runtime");
MODULE_AUTHOR("m0nk <josh@atredis.com>");
MODULE_LICENSE("GPL");

//--------------------------------------------------------
// ~ fin
//--------------------------------------------------------
