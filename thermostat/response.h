const char RESPONSE_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta charset='UTF-8'>
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
    p {
      font-size: 1.5rem;
    }
    a {
      color: #7a678e;
      font-size: 1.2rem;
    }
    a:hover {
      color: #635275;
    }
  </style>
</head>
<body>
  <div class="container">
    <p>Запрос отправлен.</p>
    <a href="/">Назад </a>
  </div>
</body>
</html>
)=====";