/* I took some files over the internet. links:
 1.https://i.imgur.com/qBYPUDH.gif
 2.https://i.imgur.com/Tsarg55.png  
 3.https://media.giphy.com/media/26tOZ42Mg6pbTUPHW/giphy.gif  
  */
const char* pageTemplate = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>New Year Countdown</title>
  <style>
    body {
      text-align: center;
      font-family: Arial, sans-serif;
      background-color: #1e1e2f;
      color: white;
      background-image: url('https://i.imgur.com/qBYPUDH.gif');
      background-size: cover;
      background-repeat: no-repeat;
    }
    h1 {
      color: #ffcc00;
      text-shadow: 0 0 10px #ffcc00, 0 0 20px #ffaa00;
    }
    h2 {
      color: red;
      font-size: 16px;
      text-shadow: 0 0 10px #ffcc00, 0 0 20px #ffaa00;
      position: absolute;
      top: 45%; 
      left: 50%; 
      transform: translate(-50%, -50%);
}

    #timezone {
      font-size: 20px;
      margin: 25px 200px 75px 1px;
      color: blue;
      text-shadow: 0 0 10px #00ffcc, 0 0 20px #00ffff;
      }
    #timer {
      font-size: 48px;
      margin-top: 15px;
      color: #00ffcc;
      text-shadow: 0 0 10px #00ffcc, 0 0 20px #00ffff;
    }
    #present {
      margin-top: 50px;
    }
    #message {
      display: none;
      margin-top: 20px;
      font-size: 24px;
      color: #00ff00;
    }

  </style>
</head>
<body>
  <h1>&#x1F386; Late New Year Countdown &#x1F386;</h1>
  <div id="timezone">%TIMEZONE%</div>
  <div id="timer">%TIME%</div>
  <h2 id="h2"> will be open at 00:00 on january 3</h2>
  <div id="present">
    <img src="https://i.imgur.com/Tsarg55.png" alt="Present" width="200"> 
  </div>
  <div id="message">As we step into a new year, I want to take a moment to thank all of you for your support and for being part of this amazing journey! May this year bring you joy, growth, and countless opportunities to learn and create. Let’s make 2025 even more exciting with new projects, discoveries, and memories. Cheers to fresh beginnings and endless possibilities! Stay curious, stay creative, and never stop dreaming!</div>

  <script>
   function fetchRemainingTime() {
    fetch('/remaining-time')
    .then(response => response.json())
    .then(data => {
      document.getElementById('timer').innerHTML = data.remainingTime;
      if (data.remainingTime === "0h 0m 0s") {
        document.body.style.backgroundImage = "url('https://media.giphy.com/media/26tOZ42Mg6pbTUPHW/giphy.gif')"; 
        document.getElementById('message').style.display = "block";
        document.getElementById('present').style.display = "none";
        document.getElementById('h2').style.display = "none";
      }
    })
    .catch(error => console.error('Error fetching remaining time:', error));
}
    setInterval(fetchRemainingTime, 1000);
  </script>
</body>
</html>
)rawliteral";
