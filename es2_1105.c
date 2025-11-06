// proc Pn
// while true {
// 	enter
// 	elabora in 3
// 	esci
// }

// Ci sono 3 processi: al primo enter, si ferma. Al secondo enter, si ferma. Al terzo si riparte.
// Utilizziamo i semafori

// Assumiamo che P e W sono già stati dichiarati e sono FIFO.

int wcount, processing;
semaphore mutex(1);
semaphore waiting(0);

enter () {
	mutex.P();
	wcount++;
	if !(wcount >= 3 && processing == 0) {
		mutex.V();
		waiting.P();
	}
	wcount--;
	processing++;
	if (processing <3) {
		waiting.V();
	} else {
		mutex.V();
	}
}

exit () {
	mutex.P();
	processing--;
	if (processing == 0 && wcount >= 3) {
		waiting.V();
	} else {
		mutex.V();
	}
	
}

