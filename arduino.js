var width = 12;
var height = 9;

var util = require('util');
var fs = require('fs');
var net = require('net');
var aws_port = 9000;

var bConnect = false; 
var aws = net.connect({ port: aws_port, host: '52.79.156.99' }, function () {
    //console.log('   local = %s:%s', this.localAddress, this.localPort);
    console.log('computer server connected = %s:%s', this.remoteAddress, this.remotePort);
    this.setEncoding('utf8');
    this.on('data', function (data) {
        //console.log(data.toString());
        if (bConnect) {
            ParseData(data);
            SetTime();
            SendTo();
        }

        if (data.toString() == 'ok') {
            writeData(this, 'arduino');
            bConnect = true;
        }

    });
    this.on('end', function () {
        console.log(' Client disconnected');
    });
    this.on('error', function (err) {
        console.log('Socket Error: ', JSON.stringify(err));
    });
    this.on('timeout', function () {
        console.log('Socket Timed Out');
    });
    this.on('close', function () {
        console.log('Socket Closed');
    });
});

var image = new Array(width);
for (var i = 0; i < image.length; i++)
    image[i] = new Array(height);

function ParseData(data) {
    for (var i = 0; i < image.length; i++) {
        for (var j = 0; j < image[i].length; j++) {
            image[i][j] = parseInt(data[i*height*2+j*2]);
        }
    }
    console.log(image);
}

var delay = new Array(width * 3);
function SetTime() {
    console.log('set time!');
    delay[0] = 0;
    for (var i = 0; i < image.length; i++) {
        var max = 0;
        for (var j = 0; j < image[i].length; j++)
            if (image[i][j] > max) max = image[i][j];
        if (i == 0) delay[i] = 0;
        else delay[i * 3] = delay[i * 3 - 1] + 2000;            // stepper moving time
        delay[i * 3 + 1] = delay[i * 3] + max * 500 + 1000;     // servo motor up + relax time
        delay[i * 3 + 2] = delay[i * 3 + 1] + max * 500 + 1000; // servo motor down + relax time
        console.log(delay[i * 3] + ', ' + delay[i * 3 + 1] + ', ' + delay[i * 3 + 2]);
    }
}
function dummy(){}
function SendTo() {
    setTimeout(dummy, 1000, "after 3sec");
    console.log('rotate!!!');
    var tempTimer = Date.now();
    var i = 0;
    var step = 0;
    var t = setInterval(tempfunc, 100);
    function tempfunc() {
        if (Date.now() - tempTimer > delay[i]) {
            if (i != 0) {
                console.log('delay : ' + (delay[i] - delay[i - 1]));
                var str = '';
                if (i % 3 == 0) { // stepper moving
                    stepper.write('1');
                    console.log('stepper moving');
                } else if (i % 3 == 1) { // servo motor up
                    for (var j = 0; j < height; j++) {
                        if (j < 9) str += ('0' + (j + 1).toString() + '1' + image[step][j]);
                        else str += ((j + 1).toString() + '1' + image[step][j]);

                        //console.log((j + 1) + ' : ' + (j + 1).toString() + '1' + image[step][j]);
                    }
                    var tmp = util.format("%s", str);
                    servo.write(tmp);
                } else { // servo motor down
                    for (var j = 0; j < height; j++) {
                        if (j < 9) str += ('0' + (j + 1).toString() + '0' + image[step][j]);
                        else str += ((j + 1).toString() + '0' + image[step][j]);

                        //console.log((j + 1) + ' : ' + (j + 1).toString() + '0' + image[step][j]);
                    }
                    var tmp = util.format("%s", str);
                    servo.write(tmp);
                    step++;
                    console.log('step ' + step + " end");
                }
            }
            if (step >= width) {
                console.log('end');
                var index = 0;
                var rollback = setInterval(function () {
                    ++index;
                    stepper.write('0');
                    if (index >= 11) clearInterval(rollback);
                }, 1500);
                clearInterval(t);
            }
            i++;
        }
    }
}

var SerialPort = require('serialport');

var servo = new SerialPort('\\\\.\\COM6', {
    baudrate: 57600,
    parser: SerialPort.parsers.readline('\n')
});
var stepper = new SerialPort('\\\\.\\COM5', {
    baudrate: 9600,
    parser: SerialPort.parsers.readline('\n')
});

servo.on('open', function () {
    console.log("servo connected!!!");
});
servo.on('data', function (data) {
    console.log("servo data : " + data);
});


stepper.on('open', function () {
    console.log("stepper connected!");
});
stepper.on('data', function (data) {
    console.log("stepper data : " + data);
});

function writeData(socket, data) {
    var success = !socket.write(data);
    if (!success) {
        (function (socket, data) {
            socket.once('drain', function () {
                writeData(socket, data);
            });
        })(socket, data);
    }
}