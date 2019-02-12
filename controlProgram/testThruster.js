var i2c = require('i2c');
const interval = require('interval-promise');
var us = require('microseconds');

addrs = [0x31, 0x32, 0x33, 0x30, 0x3A, 0x3B]//, 0x31]//, 0x31, 0x3A, 0x3B]//, 0x3A, 0x3B];

thrusters = [];
for(var a of addrs){
	thrusters.push(new i2c(a, {device:'/dev/i2c-1'}));
}

voltage = new i2c(0x70, {device: '/dev/i2c-1'});

async function writeThruster(t, speed){
	return new Promise((resolve, reject)=>{
		var start = us.now();
		t.writeBytes(0x00, [speed*32767>>>8, (speed*32767)%255], function(err){
				if(err){
					reject(err);
				}else{
					// console.log(speed + "\t" + (us.now() - start));
					resolve();
				}
		});
	});
}

async function writeThrusters(speed){
	for (var t of thrusters){
		await writeThruster(t, speed);
	}
}

async function readVoltage(){
	return new Promise( (resolve, reject)=>{
		var start = us.now();
		voltage.readBytes(0x99, 2, (err, res) => {
			if (err){
				reject(err);
			}else{
				let adc = (res[0]<<8) + (0xff & res[1]);
				// let voltage = adc / 1024 * 5;
				// voltage = Math.round(voltage, 2);
				console.log( adc + "\t" + (us.now() - start) );
				resolve();
			}
		});
	});
}

function syncWait(millis){
	return new Promise( (resolve, reject) => {
		setTimeout( ()=> { resolve(); }, millis);
	});
}

async function thrust(speed, time){
	var error = 0;
	console.log("thrust: " + speed);
	for (var i =0; i< parseInt(time / 50); i++){
		try{
		await writeThrusters(speed);
		}catch(err){
			error++;
		}
		await syncWait(50);
	}
	console.log("total error: " + error);
}
/*
var thrusterSpeed =0;
async function gradualThrust(targetSpeed,accel) {
	while(speed 
*/
// Main test logics
async function test(){
	await thrust(0, 1000);
	await thrust(-15000, 3000);
	await thrust(0, 200);
	await thrust(15000, 3000);
	await thrust(0, 1000);
}

test();




/*
interval(async() => {
	writeThrusters(2000);
}, 500, { iterations: 10 });

interval(async() => {
	writeThrusters(0);
}, 500, { iterations: 4 });*/
