var socket = io();

var state = {
	drive: 0,
	strafe: 0,
	rotate:0,
	upDown: 0,
	tilt: 0,
	HFR: 0,
	HFL: 0,
	HRR: 0,
	HRL: 0,
	VF: 0,
	VR: 0,
	direction: 0,
	fineCoarse: 0,
};

var mapping = [
   { channel: 'drive', vname: 'drive'},
   { channel: 'strafe', vname: 'strafe'},
   { channel: 'rotate', vname: 'rotate'},
   { channel: 'upDown', vname: 'upDown'},
   { channel: 'tilt', vname: 'tilt'},
   { channel: 'thrusterControl.thrust.HFR', vname: 'HFR'},
   { channel: 'thrusterControl.thrust.HFL', vname: 'HFL'},
   { channel: 'thrusterControl.thrust.HRR', vname: 'HRR'},
   { channel: 'thrusterControl.thrust.HRL', vname: 'HRL'},
   { channel: 'thrusterControl.thrust.VF', vname: 'VF'},
   { channel: 'thrusterControl.thrust.VR', vname: 'VR'},
   { channel: 'profile.direction', vname: 'direction'},
   { channel: 'profile.fineCoarse', vname: 'fineCoarse'},
];

mapping.forEach((element) => {
	var vname = element.vname;
	var channel = element.channel;
	socket.on(channel, (value) => {
		state[vname] = value;
	});
});
/*
socket.on('drive', function(value){
	state.drive = value;
});

socket.on('thruster.thrust.HFL', function(value){
	state.HFL = value;
});
*/

function setup() {
  createCanvas(800, 600);
}
/*
//for non khan academy PROCESSINGJS ONLY
var canvas = document.getElementById("mycanvas");
var context = canvas.getContext("2d");
*/
function thruster() {
    ellipse(0,-20,25,25);
    ellipse(0,20,25,25);
    rect(-30,-20,60,40);
};
function arrow(Mag) {
	stroke(0, 255, 0, abs(Mag*200) + 55);
    strokeWeight(10);
    line(0,0,0,Mag * -100);
    push();
    translate(0, -100 * Mag);
    strokeWeight(1);
    fill(0, 255, 0, abs(Mag*255));
    triangle(0, -10 * Mag, -10, 0, 10, 0);
	fill(255);
    pop();
	noStroke();
};
function printText(String, X, Y, Size) {
	textAlign(CENTER, CENTER);
	textSize(Size);
	text(String, X, Y);
};
function HorizUI(Fr,Fl,Rr,Rl) {
    push();
	var FR = ((floor(Fr * 10000)) / 10000);
    var FL = ((floor(Fl * 10000)) / 10000) * -1;
    var RR = ((floor(Rr * 10000)) / 10000);
    var RL = ((floor(Rl * 10000)) / 10000);
    translate(200,200);
    //FR
    push();
    rotate(1.75 * PI);
    translate(150,0);
    thruster();
    arrow(FR);
    pop();
	printText(FR, 100, -50, 20);
    //RR
    push();
    rotate(2.25 * PI);
    translate(150,0);
    thruster();
    arrow(RR);
    pop();
	printText(RR, 100, 50, 20);
    //RL
    push();
    rotate(1.75 * PI);
    translate(-150,0);
    thruster();
    arrow(RL);
    pop();
	printText(RL, -100, 50, 20);
    //FL
    push();
    rotate(1.25 * PI);
    translate(150,0);
    thruster();
    arrow(FL);
    pop();
	printText( -1 * FL, -100, -50, 20);
	pop();
};
function MvtOrnt(Drive, Strafe, Rotate, upDown, Tilt) {
	textSize(20);
	textAlign(LEFT,CENTER);
	text("Drive: " + ((floor(Drive * 10000)) / 10000), 40, 390);
	text("Strafe: " + ((floor(Strafe * 10000)) / 10000), 40, 415);
	text("Rotate: " + ((floor(Rotate * 10000)) / 10000), 40, 440);
	text("upDown: " + ((floor(upDown * 10000)) / 10000), 40, 465);
	text("Tilt: " + ((floor(Tilt * 10000)) / 10000), 40, 490);
};
function VertUI(Vf,Vr) {
	var VF = ((floor(Vf * 10000)) / 10000);
    var VR = ((floor(Vr * 10000)) / 10000);
	push();
	translate(475,250);
	//VF
	push();
	translate(0, 0);
	thruster();
	arrow(VF);
	printText("VF\n"  + VF, -75, 0, 20);
	pop();
	//VR
	push();
	translate(75,0);
	thruster();
	arrow(VR);
	printText("VR\n" + VR, 75, 0, 20);
	pop();
	pop();
};
//Direction, fineCoarse
function DFC(direction, finecoarse) {
	var dirText = boolean(direction) ? "Forward" : "Rear";
	var fcText = boolean(finecoarse) ? "Fine" : "Coarse";
	push();
	noStroke();
	if(boolean(direction)){
		fill(255, 0, 0, 70);
		rect(385, 387.5, 85, 25);
	} else {
		fill(0, 0, 255, 70);
		rect(385, 387.5, 60, 25)
	}
	if(boolean(finecoarse)){
		fill(255, 0, 0, 70);
		rect(403, 417.5, 60, 25);
	} else {
		fill(0, 0, 255, 70);
		rect(403, 417.5, 80, 25);
	}
	pop();
	textAlign(LEFT,TOP);
	textSize(20);
	text("Direction: " + dirText, 300, 390);
	text("fineCoarse: " + fcText, 300, 420);

};
 function DepthMeter(Depth){
	push();

	pop();
 };


function draw() {
	smooth();
    resetMatrix();
    background(255, 255, 255);
    rect(50, 50, 300, 300, 50);
    HorizUI(state.HFR, state.HFL, state.HRR, state.HRL);
	//FR, FL, RR, RL
	VertUI(state.VF, state.VR);
	//VF, VR
	MvtOrnt(state.drive, state.strafe, state.rotate, state.upDown, state.tilt);
	//Drive, Strafe, Rotate, upDown, Tilt
	DFC(state.direction, state.fineCoarse);
	//Direction, fineCoarse
};


/* Testing using var i += 0.01111111
var i = 1;
function draw() {
	smooth();
    resetMatrix();
    background(255, 255, 255);
    rect(50,50,300,300,50);
    HorizUI(i, i, i, i);
	//FR, FL, RR, RL
	VertUI(i, i);
	//VF, VR
	MvtOrnt(i, i, i, i, i);
	//Drive, Strafe, Rotate, upDown, Tilt
	DFC(false, false);
	//Direction, fineCoarse
    i+=0.01111111;
    if(i>=1){
        i=-1;
    };
};
*/
