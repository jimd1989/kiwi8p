The slider on my Kiwi-8P is busted so I'm making a shell to drop sysex commands into it. As with all my audio endeavors, I am making this solely to suit my needs, but the code will be small for anybody to hack to his or her desires.

Had to introduce a delay between parameter transmissions, so this isn't intended for realtime performance. Use CC for that. There's a nice CC:parameter mapping in the file `cc.h` that is not used in this code, but is a helpful reference.

Some bounds checking and sanitization when it's easy enough, but don't feed this bad input.

Commands are J/K style and intended to be passed `all;on;one;line`, so that each line is a discrete slice of synthesizer state. I've found this condensed view to be very useful in previous musical efforts.

Unix philosophy. Wrap this with `rlwrap`. Pipe its output to a `/dev/rmidi0` or whatever file.

| Command | Sysex byte | Description | Args |
|---------|------------|-------------|------|
| `w`/`w.` | 20/26 | wave/range of dco1/2 | wave shape: <br> s → saw <br> p → pulse <br> q → square <br> n → noise <br><br> dco2 can also take sync information: <br> y → sync1 <br> Y → sync2 <br> x → xmod <br><br> + range of 16/8/4/2 <br><br> ex: `ws16;w.qY2` |
| `t`/`t.` | 21/27 | coarse tuning of dco1/2 | [-24,24] in half semitone steps |
| `l`/`l.` | 22/29 | pitch lfo amount for dco1/2 | [0,127] |
| `e`/`e.` | 23/30 | pitch envelope amount for dco1/2 | [0,127] |
| `y`/`y.` | 24/31 | key velocity modulation of pitch for dco1/2 | [0,127] |
| `c`/`c.` | 25/32 | dco1/2 control sources | l{n} → lfo number {n} <br> e{n} → envelope number {n} <br><br> negative numbers are inverted sources <br><br> ex: `cl1e-2;c.e3l3` |
| `t:`     | 28    | dco2 fine tune | [-63,63] correlating to a resolution of +/- 50 cents |
| `t@`     | 33    | voice detuning | [0,127] |
| `V`/`V.` | 34/35 | mix volume of dco1/2 | [0,127] |
| `Y`      | 36    | key velocity modulation of dco2 mix level | [0,127] |
| `E`      | 37    | envelope amount over dco2 mix level | [0,127] |
| `C`      | 38    | mix envelope source | e{n} → envelope number {n} <br><br> negative numbers are inverted envelopes <br><br> ex: `Ce-2` |
| `f:`     | 39    | high pass filter cutoff | [0,3] |
| `f`      | 40    | low pass filter cutoff | [0,4095] <br><br> yes, it is higher res than the display suggests |
| `f.`     | 42    | low pass filter resonance | [0,4095] |
| `l@`     | 44    | filter lfo amount | [0,127] |
| `e@`     | 45    | filter envelope amount | [0,127] |
| `k@`     | 46    | filter key follow | [0,127] |
| `y@`     | 47    | key velocity modulation of filter | [0,127] |
| `c@`     | 48    | filter control sources | l{n} → lfo number {n} <br> e{n} → envelope number {n} <br><br> negative numbers are inverted sources <br><br> ex: `c@e1l-1` |
| `v`      | 49    | vca level | [0,127] |
| `l:`     | 50    | vca lfo amount | [0,127] |
| `c:`     | 51    | vca control sources | l{n} → lfo number {n} <br> e{n} → envelope number {n} <br><br> only the lfo can be inverted with a negative number <br><br> ex: `c:e2l-3` |
| `y:`     | 52    | key velocity sensitivity for vca | [0,127] |
| `q`/`q.`/`q:`/`Q`/`Q.`/`Q:` | 53/57/61/65/69/73 | modulation sources for matrix slots [1,6] | o → off <br> bu → bend up <br> bd → bend down <br> bw → bend lfo switch <br> b → bend full <br> l{n}(u) → lfo number {n}; if 'u' is added to end, lfo is unipolar; bipolar if omitted <br> s{n} → sequence track {n} output <br> c{n} → midi cc number {n}; this is not the cc channel; values [1,8] listen on actual channels [47,54] <br> e{n} → envelope number {n} <br> w → mod wheel <br> d → edit slider <br> v → key velocity <br> n → note <br> a → aftertouch <br><br> ex: `qbu;q.e2;q:s1;Qc7;Q.v;Q:a` |
| `u`/`u.`/`u:`/`U`/`U.`/`U:` | 54/58/62/66/70/74 | control sources for matrix slots [1,6] | most sources can be inverted if they are prefixed with a '-' <br><br> (-)o → fixed level <br> (-)bu → bend up <br> (-)bd → bend down <br> (-)b → bend full <br> (-)c{n} → midi cc number {n} <br> s{n} → output of sequence {n} <br> (-)w → mod wheel <br> (-)d → edit slider <br> (-)a → aftertouch <br><br> ex: `ua;u.bu;u:s4;U-w;U.-c3;U:b` |
| `x`/`x.`/`x:`/`X`/`X.`/`X:` | 55/59/63/67/71/75 | modulation levels of matrix slots [1,6], governed by control sources | [0,127] |
| `z`/`z.`/`z:`/`Z`/`Z.`/`Z:` | 56/60/64/68/72/76 | modulation targets of matrix slots [1,6] | o → off <br> p1 → dco1 frequency <br> p2 → dco2 frequency <br> p → both dco frequencies <br> w{n} → wave shape of dco{n} <br> r{n} → frequency ranges of dco{n} <br> m{n} → mix level of dco{n} <br> f. → lowpass filter resonance <br> f: → highpass filter cutoff <br> f → lowpass filter cutoff <br> l{n} → lfo{n} rate <br> e{n} → env{n} speed <br> d → detune amount <br> v → vca level <br> P → portamento rate <br><br> ex: `zp1;z.w1;z:l3;ZP;Z.v;Z:f` |
| `a`/`a.`/`a:` <br> `d`/`d.`/`d:` <br> `s`/`s.`/`s:` <br> `r`/`r.`/`r:` | 77/82/87 <br> 78/83/88 <br> 79/84/89 <br> 80/85/90 | attack/decay/sustain/release values of env1/2/3 | [0,127] |
| `W`/`W.`/`W:` | 92/96/100 | wave shape of lfo1/2/3 | i → sine <br> t → triangle <br> q → square <br> s → saw <br> S → reverse saw <br> r → random | 
| `R`/`R.`/`R:` | 93/97/101 | rate of lfo1/2/3 | [0,127] |
| `D`/`D.`/`D:` | 94/98/102 | delay of lfo1/2/3 | [0,127] |
| `N`/`N.`/`N:` | 95/99/103 | control of lfo1/2/3 | (+){n}, where {n} is one of the following clock sync values <br><br> 0 → free running <br> 2 → two whole notes <br> 1.5 → dotted whole note <br> 1 → whole note <br> 1.25 → dotted half note <br> 1.2 → half note <br> 1.45 → dotted quarter note <br> 1.4 → quarter note <br> 1.85 → dotted eighth note <br> 1.43 → quarter note triplet <br> 1.8 → eighth note <br> 1.83 → eighth note triplet <br> 1.16 → sixteenth note <br> 1.163 → sixteenth note triplet <br> 1.32 → thirty-second note <br> 1.323 → thirty-second note triplet <br> 1.64 → sixty-fourth note <br><br> prefixing the number with '+' makes the lfo additive <br><br> ex: `N+0;N.1.32;N:1.43` |
| `O` | 104 | chorus type | [0,2], where 0 is off and {n} is chorus type {n} |
| `p` | 105 | portamento rate | [0,127] |
| `s@` | 106 | load sequence | [0,8] where 0 doesn't load a sequence, and {n} is sequence {n} |
| `i` | 107 | voice controls | {p}(l)(r) where {p} is one of the following polyphony modes: <br><br> s → 1 voice per key <br> d → 2 voices per key <br> t → 3 voices per key <br> u → 6 voices per key <br> S → 1 voice per key, but monophonic <br><br> adding r reassigns voices instead of rotating them <br><br> adding l engages legato behavior of envelopes <br><br> ex: `ildr` |
| `i.` | 108 | voice stealing behavior | o → steal oldest voice <br> n → steal newest voice <br> h → steal highest pitched voice <br> l → steal lowest pitched voice <br> q → steal quietest voice <br> i → ignore any new voice |
| `A` | 109 | arp control | {n}{a} where {n} is an octave range [1,4] and {a} is one of the following: <br><br> u → play arp up <br> d → play arp down <br> b → play arp up/down <br> r → play arp randomly <br> p → play arp in order of key presses <br><br> ex: `A2u` |
| `A.` | 110 | aftertouch routings | (l)(f)(v) in parallel: <br><br> l → dco lfo <br> f → filter cutoff <br> v → vca level <br><br> ex: `A.lf` | 
| `b.` | 111 | modwheel routings | (l)(f)(v) in parallel: <br><br> l → dco lfo <br> f → filter cutoff <br> v → vca level <br><br> ex: `b.fvl` | 
| `b:` | 112 | modwheel level | [0,127] |
| `S` | 113 | performance switches | (a)(s)(h) in parallel: <br><br> a → enable arp <br> s → play sequence <br> h → hold note <br><br> ex: `Sash` |
| `T` | 114 | internal clock rate | [0,4095] correlating to [5,300]bpm |
| `T.` | 116 | arp clock divide | 1.2 → half note <br> 1.4 → quarter note <br> 1.8 → eighth note <br> 1.85 → eighth note half swing <br> 1.89 → eighth note full swing <br> 1.83 → eighth note triplet <br> 1.16 → sixteenth note <br> 1.165 → sixteenth note half swing <br> 1.169 → sixteenth note full swing <br> 1.163 → sixteenth note triplet <br> 1.32 → thirty-second note <br> 1.323 → thirty-second note triplet <br> 1.64 → sixty-fourth note |
| `T:` | 117 | sequence clock divide | 1.2 → half note <br> 1.4 → quarter note <br> 1.8 → eighth note <br> 1.85 → eighth note half swing <br> 1.89 → eighth note full swing <br> 1.83 → eighth note triplet <br> 1.16 → sixteenth note <br> 1.165 → sixteenth note half swing <br> 1.169 → sixteenth note full swing <br> 1.163 → sixteenth note triplet <br> 1.32 → thirty-second note <br> 1.323 → thirty-second note triplet <br> 1.64 → sixty-fourth note |
| `b` | 118 | bend range | [0,127] representing a +/- octave span at 127 |
| `S.` | 119 | sequence control | (o)(k)(t)(r)(c) in parallel: <br><br> o → oneshot mode <br> k → key down play <br> t → auto transpose <br> r → auto transpose reset <br> c → sequence complete <br><br> ex: `S.kt` | 
| `S:` | 120 | sequence transpose | [-12,24] semitone transpose of sequence; only works if `S.t` is enabled | 
| `A:` | 121 | analog feel level | [0,127] |
