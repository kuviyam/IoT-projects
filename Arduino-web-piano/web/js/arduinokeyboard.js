var TotalOctaves = 3;
var firstOctave = 3;
var soundSelect = 0;

var record = '';
var recordData = '';

var __audioSynth = new AudioSynth();
__audioSynth.setVolume(0.5);


var keymap = {
	0: 'C',
	1: 'C#',
	2: 'D',
	3: 'D#',
	4: 'E',
	5: 'F',
	6: 'F#',
	7: 'G',
	8: 'G#',
	9: 'A',
	10: 'A#',
	11: 'B',
}

var keyState = new Array(36);

function initialize(){
	for (i = 0; i <= 11; i++) {
		visualKeyGrey(keymap[i],'6');
		visualKeyRelease(keymap[i],'3');
	}
}

function visualSelectOctave(sel){
	if(sel=='3'){
		firstOctave = 3;
		for (i = 0; i <= 11; i++) {
			visualKeyGrey(keymap[i],'6');
			visualKeyRelease(keymap[i],'3');
		}
	}
	if(sel=='4'){
		firstOctave = 4;


		for (i = 0; i <= 11; i++) {
			visualKeyGrey(keymap[i],'3');
			visualKeyRelease(keymap[i],'6');
		}
	}
}

function visualSelectInstrument(sel){
	soundSelect = sel;
}


function processKeys(key_values){
	if(key_values[36]=='0'){
		record = 'True';
		document.getElementById("record_button").checked = true;
	}
	else {
		record = 'False';
		document.getElementById("record_button").checked = false;
	}
	// octave selection
	if(key_values[37]=='0'){
		firstOctave = 3;
		document.getElementById("radio_oct_sel1").checked = true;

		for (i = 0; i <= 11; i++) {
			visualKeyGrey(keymap[i],'6');
			visualKeyRelease(keymap[i],'3');
		}

	}
	if(key_values[38]=='0'){
		firstOctave = 4;
		document.getElementById("radio_oct_sel2").checked = true;
		for (i = 0; i <= 11; i++) {
			visualKeyGrey(keymap[i],'3');
			visualKeyRelease(keymap[i],'6');
		}
	}
	// set instrument
	if(key_values[39]=='0'){
		soundSelect = 0;
		document.getElementById("radio1").checked = true;
	}
	if(key_values[40]=='0'){
		soundSelect = 1;
		document.getElementById("radio2").checked = true;
	}
	if(key_values[41]=='0'){
		soundSelect = 2;
		document.getElementById("radio3").checked = true;
	}


	var i,octTmp;
	for (octTmp = 0; octTmp < TotalOctaves; octTmp++){
		if(octTmp=='0'){
			keyoct = 0;
		}
		if(octTmp=='1'){
			keyoct = 12;
		}
		if(octTmp=='2'){
			keyoct = 24;
		}
		for (i = 0; i <= 11; i++) {
			if(key_values[i+keyoct]=='0' && keyState[i+keyoct] != 'Pressed'){
				keyState[i+keyoct] = 'Pressed';
				playNote(keymap[i], (firstOctave + octTmp).toString());
				visualKeyPress(keymap[i], (firstOctave + octTmp).toString());
				if(record == 'True') {
					recordData = recordData + keymap[i] + (firstOctave + octTmp).toString();
					document.getElementById("notesdata").innerHTML = recordData;
				}
				else if(record == 'False') {
					recordData = '';
					document.getElementById("notesdata").innerHTML = recordData;
				}
			}
		}

		for (i = 0; i <= 11; i++) {
			if(key_values[i+keyoct]=='1' && keyState[i+keyoct] != 'Released'){
				keyState[i+keyoct] = 'Released';
				visualKeyRelease(keymap[i], (firstOctave + octTmp).toString());
			}
		}
	}
}


function playNote(note, octave){
	src = __audioSynth.generate(soundSelect, note, octave, 2);
	container = new Audio(src);
	container.addEventListener('ended', function() { container = null; });
	container.addEventListener('loadeddata', function(e) { e.target.play(); });
	container.autoplay = false;
	container.setAttribute('type', 'audio/wav');
	container.load();
	return container;
}


function visualKeyPress(note, octave){
	cur_note = note + octave;
	document.getElementById(cur_note).style.backgroundColor = 'rgb(27, 192, 234)';
	document.getElementById(cur_note).style.marginTop = '5px';
	document.getElementById(cur_note).style.boxShadow = 'none';
}

function visualKeyRelease(note, octave){
	cur_note = note + octave;
	document.getElementById(cur_note).style.backgroundColor = '';
	document.getElementById(cur_note).style.marginTop = '';
	document.getElementById(cur_note).style.boxShadow = '';
}

function visualKeyGrey(note, octave){
	cur_note = note + octave;
	document.getElementById(cur_note).style.backgroundColor = 'rgb(224, 224, 224)';
	document.getElementById(cur_note).style.marginTop = '';
	document.getElementById(cur_note).style.boxShadow = '';
}