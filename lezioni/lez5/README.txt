GUARDA IN QUESTO TXT L'ORDINE PER ESEGUIRE I FILE:

Per vedere che cos'è una system call -> esempio_execve -> exec1_ERRATO -> exec2_CORRETTO

I programmi exec1 SCAMBIANO un processo con un altro. Per lanciare PIÙ PROCESSI CONTEMPORANEAMENTE bisogna utilizzare fork.

Come finisce un processo?
Noi vediamo quando facciamo return 0, ma come detto, i processi o vengono uccisi o si suicidono.
La system call _exit lo fa:
Se facciamo un programma che fa _exit(42), il processo viene sempre ucciso. Se si fa ./nomeprogramma e si fa echo $?, ci darà 42.

Dove vengono salvate le variabili?
In uno stack. Quando il figlio viene generato, si crea uno stack copia diverso da quello genitore.

Quando noi facciamo ps ax | grep ./(nome programm), ci darà i processi attivi per quel programma. (Se lo facciamo mentre il figlio fa wait, ci da il processo genitore e figlio)

Programma zombie1.c -> zombie2.c

Zombie:
Se compili il codice zombie, il processo viene messo su ps ax. è morto ma sta aspettando che venga pulito (wait(60)) dal padre.
È morto perchè ha finito il suo lavoro _exit(42) e non serve più a nulla.
Il sistema operativo lo tiene ancora là perchè deve consegnare il suo codice di uscita, ovvero 42.
Appena il padre si sveglia e chiama wait(), raccoglie il codice di uscita. Solo in quel caso viene definitivamente ucciso.


