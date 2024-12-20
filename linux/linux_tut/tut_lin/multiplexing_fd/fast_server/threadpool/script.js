const progress = document.getElementById("progress");
const prev = document.getElementById("prev");
const next = document.getElementById("next");
const circles = document.querySelectorAll(".circle");
const start = document.getElementById("start");

let currentActive = 1;

next.addEventListener("click", () => {
    currentActive++;
    if (currentActive > circles.length) currentActive = circles.length;
    update();
});

prev.addEventListener("click", () => {
    currentActive--;
    if (currentActive < 1) currentActive = 1;
    update();
});

const update = () => {
    circles.forEach((circle, index) => {
        if (index < currentActive) circle.classList.add("active");
        else circle.classList.remove("active");
    });
    const actives = document.querySelectorAll(".active");
    progress.style.width =
        ((actives.length - 1) / (circles.length - 1)) * 100 + "%";
    if (currentActive === 1) prev.disabled = true;
    else if (currentActive === circles.length) next.disabled = true;
    else {
        prev.disabled = false;
        next.disabled = false;
    }
};

var xhr = new(XMLHttpRequest);
start.addEventListener("click", startString);
var idTimer1;
var temp = false;
var ctx = document.getElementById("myChart");
function Timer1() {
    //xhr.open("GET", "content.bin", true);
    xhr.open("GET", "content.bin?r=" + Math.random(), true);
    xhr.responseType = "arraybuffer";
    xhr.onload = function (oEvent) {
        var val = new Uint32Array(this.response);
        //console.log(val);
        myChart.data = val[0];
        draw(val);
    }
    xhr.send(null);
    idTimer1 = setTimeout("Timer1()", 1);
}

var IsStarted = false;
function startString() {
    if(!IsStarted) {
        IsStarted = true;
        document.getElementById('start').innerHTML = 'STOP';
        Timer1();
    } else {
        IsStarted = false;
        clearTimeout(idTimer1);
        document.getElementById('start').innerHTML = 'START';
    }
}

function draw(i) {
    i = i % 4096;
    var V = (3.3*i/4096)
    var canvas = document.getElementById('myChart');
    if (canvas.getContext) {
        var ctx = canvas.getContext('2d');
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        ctx.fillStyle = "red";
        ctx.fillRect(0, 0, canvas.width*V/3.3, 50);
        ctx.fillStyle = "blue";
        ctx.font = "italic 30pt Arial";
        ctx.fillText(V.toFixed(3) + "V", 35, 150);
    }
}
