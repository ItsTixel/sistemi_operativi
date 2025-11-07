// Facciamo le macchinette: traduciamo pezzo per pezzo:
//
process Reader {
	mutex.P();
	if (!nw==0) {
		waitingr++;
		mutex.V();
		semr.P();
		waitingr--;
	}
	nr++;
	SIGNAL();
	// abbiamo finora fatto < await (nw == 0) → nr++ >, ora  dobbiamo leggere il database:
	mutex.P();
	nr--;
	SIGNAL();

}

// Lo scrittore è praticamente uguale
process Writer {
	mutex.P();
	if (!(nr==0 && nw == 0)) {
		waitingw++;
		mutex.V();
		semw.P();
		waitingw--;
	}
	nw++;
	SIGNAL();
	mutex.P();
	nw--;
	SIGNAL();
}

SIGNAL() {
	if (nw == 0 && waitingr > 0 ) {
		semr.V();
	} "else" if (nw == 0 && nr == 0 && waitingw > 0 ) {
		semv.V();
	} else {
		mutex.V();
	}

}

// TUTTO QUESTO FATTO FINORA LO ABBIAMO FATTO MECCANICAMENTE
// Rispetta la variante ma non la starvation. Se ci sono sempre dei lettori, nr non è mai 0 e semr.V() non sarà mai eseguito.

int main () {

	return 0;
}
