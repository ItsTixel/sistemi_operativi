semaphore s1(1);
semaphore s2(1);
semaphore mutex(1)
int n=0;

Thread A {
	register int i;
	for (i=1;i<3;i++) {	// lo fa due volte
		s1.P(); 
		mutex.P()
		// CRITICAL SECTION
		n+=i; 	// Somma n+= 1 o n+=2
		mutex.V()
		s2.V();
		// EXIT CRITICAL SECTION
	}
}

Thread B {
	register int j;
	for (j=2;j<4;j++) {
		s2.P();
		mutex.P()
		// CRITICAL SECTION
		n*=j; // Moltplica n*=2 o n*=3
		mutex.V()
		s1.V();
		// EXIT CRITICAL SECTION
	}
}

// I possibili cammini sono:
// - n+1, n*2, n+2, n*3
// - n+1, n*2, n*3, n+2
// - n*2, n+1, n+2, n*3
// - n*2, n+1, n*3, n+2
//
// Con n=0, si può fare:
// n=0
// n=1       | n=0
// n=2       | n=1
// n=4 : n=6 | n=3 : n=3
// n=12: n=8 | n=5 : n=9
