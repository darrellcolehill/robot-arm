
var socket = io.connect('http://localhost:8080');

//X-axis button setup
var left = document.getElementById('left');
var right = document.getElementById('right');
//Y-axis (1) button setup
var up1 = document.getElementById('up1');
var down1 = document.getElementById('down1');
//Y-axis (2) button setup
var up2 = document.getElementById('up2');
var down2 =document.getElementById('down2');
//Claw button setup (default position is open)
var claw = document.getElementById("claw");
var clawStatus = "open";


//Client side code for x-axis/base servo
left.addEventListener("mousedown", function(){
	socket.emit('startLeft');
});
right.addEventListener("mousedown", function(){
	socket.emit('startRight');
});

left.addEventListener("mouseup", function(){
	socket.emit('stopLeft');
});
right.addEventListener("mouseup", function(){
	socket.emit('stopRight');
});


//Client side code for y-axis (1) servo
up1.addEventListener("mousedown", function(){
	socket.emit('startUp1');
});
down1.addEventListener("mousedown", function(){
	socket.emit('startDown1');
});

up1.addEventListener("mouseup", function(){
	socket.emit('stopUp1');
});
down1.addEventListener("mouseup", function(){
	socket.emit('stopDown1');
});


//Client side code for y-axis (2) servo
up2.addEventListener("mousedown", function(){
	socket.emit('startUp2');
});
down2.addEventListener("mousedown", function(){
	socket.emit('startDown2');
});

up2.addEventListener("mouseup", function(){
	socket.emit('stopUp2');
});
down2.addEventListener("mouseup", function(){
	socket.emit('stopDown2');
});


claw.addEventListener("click", moveClaw);

function moveClaw(){
		if(clawStatus == "open"){
		socket.emit("closeClaw");
		clawStatus = "close";
	} else {
		socket.emit("openClaw");
		clawStatus = "open";
	}
}

