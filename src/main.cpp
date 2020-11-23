#include "InputStream.h"
#include "OutputStream.h"
#include <iostream>
#include "Experiment1.h"
#include "Experiment4.h"
#include "Measurement.h"
#include <windows.h>

using namespace std;

int main() {
//    Experiment1 experiment1;
//    double *times = experiment1.getDurations("../data/aka_name.csv", 70);
//    cout << times[0] << " " << times[1] << " " << times[2] << endl;

    Experiment1 experiment1;
    Measurement *m = new Measurement();
    double *times = m->getAverageTimesB("../data/comp_cast_type.csv", 10, 1, 10);
    cout << times[9] << endl;
//    Chrono *chrono = new Chrono();
//    double *times = (double *) malloc(110 * sizeof(double));
//    for (int i = 10; i < 121; i++) {
//        chrono->startChrono();
//        experiment1.length3("../data/aka_name.csv", i);
//        times[i - 10] = chrono->getChrono();
//    }
//    double sum = 0;
//    for (int i = 0; i < 110; i++) {
//        cout << times[i] << endl;
//    }
//    free(times);
//    cout << sum / 100 << endl;

    /*
    OutputStream outputStream("file_test");
    outputStream.create();
    outputStream.writeln3("Bonjoureee grg porpe");
    outputStream.writeln3("Bonjoureee gjppppppppppppppppppppp");
    outputStream.close();
     */

//    Experiment4 experiment4;
//    experiment4.rrmerge11("../data/aka_title.csv", "../data/aka_name.csv", NULL);

    /*
    InputStream inputStream ("../data/aka_title.csv");
    inputStream.open();
    int i =0;
    while (i<11915) {
        inputStream.readln4(5);

        i++;
    }
    inputStream.close();
     */
    return 0;
}

