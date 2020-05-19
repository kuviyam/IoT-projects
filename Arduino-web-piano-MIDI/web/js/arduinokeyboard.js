// Globals to access them later.
let midiIn = [];
let notesOn = new Map();
connect();


var TotalOctaves = 3;
var firstOctave = 3;
var soundSelect = 0;

var duration = 2;
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


function processKeys(key_values, switch_values, joy_values, knob_value, slider_values){
	if(switch_values[0]=='0'){
		record = 'True';
		document.getElementById("record_button").checked = true;
	}
	else {
		record = 'False';
		document.getElementById("record_button").checked = false;
	}
	// octave selection
	if(switch_values[1]=='0'){
		firstOctave = 3;
		document.getElementById("radio_oct_sel1").checked = true;

		for (i = 0; i <= 11; i++) {
			visualKeyGrey(keymap[i],'6');
			visualKeyRelease(keymap[i],'3');
		}

	}
	if(switch_values[2]=='0'){
		firstOctave = 4;
		document.getElementById("radio_oct_sel2").checked = true;
		for (i = 0; i <= 11; i++) {
			visualKeyGrey(keymap[i],'3');
			visualKeyRelease(keymap[i],'6');
		}
	}
	// set instrument
	if(switch_values[3]=='0'){
		soundSelect = 0;
		document.getElementById("radio1").checked = true;
	}
	if(switch_values[4]=='0'){
		soundSelect = 1;
		document.getElementById("radio2").checked = true;
	}
	if(switch_values[5]=='0'){
		soundSelect = 2;
		document.getElementById("radio3").checked = true;
	}

	duration = (slider_values[2]/100 || 0.4) + 0.4;


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
				playNote(keymap[i], (firstOctave + octTmp).toString(), duration);
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


function playNote(note, octave, duration){
	document.getElementById("notesdata").innerHTML += note+octave;
	src = __audioSynth.generate(soundSelect, note, octave, duration);
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


// Start up WebMidi.
function connect() {
  navigator.requestMIDIAccess()
  .then(
    (midi) => midiReady(midi),
    (err) => console.log('Something went wrong', err));
}

function midiReady(midi) {
  // Also react to device changes.
  midi.addEventListener('statechange', (event) => initDevices(event.target));
  initDevices(midi);
}

function initDevices(midi) {
  // Reset.
  midiIn = [];
  midiOut = [];

  // MIDI devices that send you data.
  const inputs = midi.inputs.values();
  for (let input = inputs.next(); input && !input.done; input = inputs.next()) {
    midiIn.push(input.value);
  }

  displayDevices();
  startListening();
}

function displayDevices() {
  selectIn.innerHTML = midiIn.map(device => `<option>${device.name}</option>`).join('');

}

function startListening() {
  outputIn.innerHTML = '';

  // Start listening to MIDI messages.
  for (const input of midiIn) {
    input.addEventListener('midimessage', midiMessageReceived);;
  }
}


function midiMessageReceived(event) {
  // MIDI commands we care about. See
  // http://webaudio.github.io/web-midi-api/#a-simple-monophonic-sine-wave-midi-synthesizer.
  const NOTE_ON = 9;
  const NOTE_OFF = 8;

  const cmd = event.data[0] >> 4;
  const pitch = event.data[1];
  const velocity = (event.data.length > 2) ? event.data[2] : 1;

  // You can use the timestamp to figure out the duration of each note.
  const timestamp = Date.now();

  octave_org = Math.floor((pitch-36)/12);
  octave = octave_org + 3;
  key_name = keymap[pitch-(36+octave_org*12)];


  // Note that not all MIDI controllers send a separate NOTE_OFF command for every NOTE_ON.
  if (cmd === NOTE_OFF || (cmd === NOTE_ON && velocity === 0)) {
  		visualKeyRelease(key_name, octave); // -------------------------------------------
    	// outputIn.innerHTML += `note off: pitch:<b>${pitch}</b>, velocity: <b>${velocity}</b> <br/>`;

    // Complete the note!
    const note = notesOn.get(pitch);
    if (note) {
      //outputIn.innerHTML += `pitch:<b>${pitch}</b>, duration:<b>${timestamp - note}</b> ms. <br>`;
      notesOn.delete(pitch);
    }
  } else if (cmd === NOTE_ON) {
  	    playNote(key_name, octave, duration);
    	visualKeyPress(key_name, octave); // -------------------------------------------
    	// outputIn.innerHTML += `note on: pitch:<b>${pitch}</b>, velocity: <b>${velocity}</b> <br/>`;

    // One note can only be on at once.
    notesOn.set(pitch, timestamp);
  }

}