const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
</style>
<body>
<div>
  <h2>Temperature: <span id="thermoValue">0</span> &deg;C</h2>
  <form action="/getThreshold">
  Threshold: <input type="number" step="0.1" name="threshold_input" value="%THRESHOLD%" required><br>
   </head><body>
  <input type="submit" value="Save">
  </form>
</div>
<script>

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
}, 2000); //2000mSeconds update rate

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("thermoValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readValue", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";