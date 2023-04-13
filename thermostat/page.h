const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
  .container {
    position: absolute;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    border: 2px solid #7a678e;
    padding: 30px 50px;
    border-radius: 5px;
    text-align: center;
  }
  span {
    color: #7a678e;
  }
  .temperature {
    font-size: 2rem;
  }
  input[type="number"] {
    outline: 0;
    border-width: 0 0 2px;
    border-color: #9e8ab4;
  }
  input[type="number"]:focus {
    border-color: #635275;
  }
  input[type="submit"], button {
    margin-top: 10px;
    background-color: #7a678e;
    border: none;
    padding: 5px 10px;
    border-radius: 5px;
    color: white;
  }
  input[type="submit"]:hover, button:hover {
    cursor: pointer;
    background-color: #635275;
  }
  .threshold {
    font-size: 1.1rem;
  }
</style>
<body>
<div class="container">
  <p class="temperature">Temperature: <span id="thermoValue">0</span> <span>&deg;C</span></p>
  <form action="/getThreshold">
  Threshold:
  <input type="number" step="0.1" name="threshold_input" value="%THRESHOLD%" required placeholder="0"><br>
  <input type="submit" value="Save">
  </form>
  <p class="threshold">Current threshold: <span id="thresholdValue">554</span></p>
  <button onClick="changeMode()" id="modeBtn">Manuel Off</button>
</div>
<script>

function readThreshold() {
  let xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("thresholdValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readThreshold", true);
  xhttp.send();
}

readThreshold();

setInterval(function() {
  getData();
}, 2000);

function getData() {
  let xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("thermoValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readValue", true);
  xhttp.send();
}

function changeMode() {
  let xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("modeBtn").innerHTML =
      this.responseText == "1" ? "Manuel On" : "Manuel Off";
    }
  }
  xhttp.open("GET", "toggleMode", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";