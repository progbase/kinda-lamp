# Puppies - Kinda-lamp

+ Рік випуску : 2017 <BR>
+ Версія : 1.0.1 <BR>
+ Розробник : Puppies <BR>

## Схеми підключення модулів

Схему підключення датчика освітленности можна побачити [тут](https://lesson.iarduino.ru/page/podklyuchaem-bh1750-datchik-osveschennosti-gy-30-gy-302-k-arduino/). <BR>
Схему підключення сервоприводів можна побачити [тут](http://4.bp.blogspot.com/-zCq3t300cRE/UDznMIL6G7I/AAAAAAAAAcU/00JGKP7zIkw/s1600/arduino-servo.jpg). <BR>
[Тут](http://bigbarrel.ru/wp-content/uploads/2015/10/led_arduino_npn_pnp.png) знайдете схему підключення діодної стрічки. <BR>
Як підключити мікрофони побачите [тут](http://роботехника18.рф/как-подключить-датчик-звука-к-ардуино/).<BR>
Щоб підключити тач-панель скористайтесь [цим](https://geektimes.ru/post/257300/).<BR>

## Завантаження коду на плату Arduino Uno

Для завантаження коду на плату необхідно спочатку завантажити Arduino IDE.<BR>
Після встановлення програми, підключіть плату до комп'ютера за допомогою USB кабеля. <BR>
Натисність кнопку Upload - цим програма завантажиться до плати. <BR>

## Керування лампою

![kinda-lamp](https://lh5.googleusercontent.com/ZKkSusXs6RtC2AhYdLU0eKv_K6eczmXC25l4qkemWmjMQ12L21VkqeEFP7CnJMOyHQurbRCqXsVXVic=w1332-h777-rw)<BR>
Після підключення лампи, ви можете увімкнути автоматичний режим, або ручний. За замовчуванням увімкнено ручний режим керування.<BR>
У автоматичному режимі лампа сама налаштує яскравість, в залежності від навколишнього освітлення.<BR>
Керування у ручному режимі здийснюється за допомогою тач-панелі.<BR>
![touch_panel_photo](https://lh4.googleusercontent.com/1QN82f3cbMBqGdqb7p-G0HQ-MJ1I--A8viVQNOj69m4hOnJKGwQAur-uFhDenulofCXWL9DH71gbjH8=w1332-h777-rw)<BR>
У ручному режимі ви можете увімкнути або вимкнути лампу повністю,<BR>
![shining_lamp](https://lh3.googleusercontent.com/JoKLZEBa-clj7zk9KWNpCpmRFzeUwUxj944kZRCRJaQX0nF3eY6Q-wkuKZzM92i7KV7-jQm7vZ7oRSE=w1332-h777-rw)<BR>
увімкнути один із двох кольорів (жовтий або білий), увімкнути один, чи обидва кольори на 50% яскравості.<BR>
Також ви можете керувати лампою за допомогою звуку. Для цього після правильного розташуваня мікрофонів, плесніть у долоні.<BR> Kinda-lamp повернеться на джерело звуку.<BR>
