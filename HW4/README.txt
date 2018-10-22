grdpiPi

INPUT           RETURN VALUE
Input(10)     = 3.52
Input(100)    = 3.1812
Input(1000)   = 3.14554
Input(10000)  = 3.14199

big-O = n^2

INPUT           RUN TIME(s)
Input(10)     = 0.004
Input(100)    = 0.004
Input(1000)   = 0.012
Input(10000)  = 0.602
Input(100000) = 60.380 


gridpi2
INPUT           RETURN VALUE
Input(10)     = 3.52
Input(100)    = 3.1812
Input(1000)   = 3.14554
Input(10000)  = 3.14199

INPUT           RUN TIME(s)
Input(10)     = 0.004
Input(100)    = 0.004
Input(1000)   = 0.005
Input(10000)  = 0.102


I expected gridpi to run at O = n^2. Using only 10^1 - 10^4 made it hard to evaluate that prediction since 10^1 and 10^2 run very quickly and therefore are not easy to compare. I included 10^5 because its relationship to 10^4 demonstarates with my prediction. The outputs for gridpi2 were the same as in the first version, but the run times were faster. All of the inputs ran at the minumum run time that is reported by "time" except for 10^4, because the amount of steps within the constexpr function were maximized. Interestingly, its run time was consistently faster than in gridpi, possibly because the body of pyth was changed in gridpi2 since std::hypot cannot be run at compile time.
