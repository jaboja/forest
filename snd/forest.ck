TriOsc snd1 => NRev r => dac;
.1 => snd1.gain;
.15 => r.mix;
0 => int longTime;
2 => int fx;

[ 1.0, 2.0, 5.0, 7.0, 9.0 ] @=> float hi[];
float empty[0];
[ empty, empty, empty, empty ] @=> float history[][];

Std.atof( me.arg(0) ) => float timeMultiplier;
if(timeMultiplier <= 0.0) 1.0 => timeMultiplier;

// Play a note with optional FX
fun void note(float n, dur howLong) {
    timeMultiplier *=> howLong;
    
    // No FX
    if(fx > 1) {
        Std.mtof(n) => snd1.freq;
        howLong => now;
        return;
    }
    
    if(fx == 1) {
        // Going down.
        for(now + howLong => time later; now < later; 1::samp => now) {
            (later - now) / howLong => float d;
            Std.mtof(n - 0.5 + d) => snd1.freq;
        }
    } else {
        // Going up.
        for(now + howLong => time later; now < later; 1::samp => now) {
            (later - now) / howLong => float d;
            Std.mtof(n + 0.5 - d) => snd1.freq;
        }
    }
}

OscSend xmit;
xmit.setHost("localhost", 12000);

while(true) {
    Math.random2(0, 5) => fx;
    xmit.startMsg("/particle");
    
    if(Math.random2(0, 4) == 0) {
    // Repetitions of 1, 2 or 4 previous seconds
        (history.cap() >> Math.random2(0, 2)) => int n;
        Math.random2(-2, 4) * 6 => int octaveShift;
        //verse();
        for(n - 1 => int i; i >= 0; i--) {
            //verse();
            if(history[i].cap() == 0) {
                snd1 =< r;
                timeMultiplier::second => now;
                snd1 => r;
            } else {
                history[i].cap() => int n;
                for(0 => int j; j < n; j++)
                    note(history[i][j] + octaveShift, 1::second / n);
            }
        }
    } else {
    // Generation of new music
        // verse();
        for(history.cap() - 1 => int i; i > 0; i--)
            history[i - 1] @=> history[i];
        
        if(Math.random2(0,15) == 0) {
            snd1 =< r;
            timeMultiplier::second => now;
            empty @=> history[0];
            snd1 => r;
        } else {
            Math.random2(0, 4) => int n;
            if(n == 4) 3 => n;
            (1 << n) => n;
            
            float notes[n];
            for(0 => int i; i < n; i++) {
                45 + Math.random2(1,4) * 12 + hi[
                    Math.random2(0, hi.cap()-1)
                ] => notes[i];
                
                note(notes[i], 1::second / n);
            }
            notes @=> history[0];
        }
        
        // Change third and fifth note in array every ten seconds
        // to make the music more variable
        longTime + 1 => longTime;
        if(longTime >= 30)
            0 => longTime;
        <<< longTime / 10 >>>;
        (longTime / 10) + 4 => hi[2];
        (longTime / 10) + 9 => hi[4];
        if(hi[4] == 10)
            0 => hi[4];
    }
    
    if(Math.random2(0, 20) == 0) {
        <<< "Randomization." >>>;
        for(0 => int i; i<hi.cap(); i++)
            Math.random2(0,11) => hi[i];
    }
}