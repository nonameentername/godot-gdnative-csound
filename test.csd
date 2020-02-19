<CsoundSynthesizer>
<CsOptions>
-i adc -o dac -B 4096 -+rtmidi=NULL -M0 --midi-key-cps=4 --midi-velocity-amp=5 -n
</CsOptions>
<CsInstruments>

sr = 44100
ksmps = 128
nchnls = 2
0dbfs = 1


instr 1

iFreq = p4
iAmp = p5
iAtt = 0.1
iDec = 0.4
iSus = 0.6
iRel = 0.7
;iCutoff = 5000
;kCutoff ctrl7  1, 1, 1000, 3000
kCutoff chnget "cutoff"

iRes = .4
kEnv madsr iAtt, iDec, iSus, iRel
aVco vco2 iAmp, iFreq
aLp moogladder aVco, kCutoff*kEnv, iRes
;out aLp*kEnv
outs aLp*kEnv, aLp*kEnv
endin


instr 2

iFreq = p4
iAmp = p5
iAtt = 0.9
iDec = 0.4
iSus = 0.5
iRel = 0.7
;iCutoff = 5000
;kCutoff ctrl7  1, 56, 1000, 3000
kCutoff chnget "cutoff"

iRes = .4
kEnv madsr iAtt, iDec, iSus, iRel
aVco vco2 iAmp, iFreq
aLp moogladder aVco, kCutoff*kEnv, iRes
;out aLp*kEnv
outs aLp*kEnv, aLp*kEnv
endin


</CsInstruments>
<CsScore>
f0 3600
</CsScore>
</CsoundSynthesizer>
