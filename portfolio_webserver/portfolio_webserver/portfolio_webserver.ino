#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "wifi"; // Your WiFi SSID
const char* password = "password"; // Your WiFi Password

WebServer server;

// HTML and CSS content
const char* htmlContent = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dharanish's Portfolio</title>
    <style>
        body {
            font-family: 'Arial', sans-serif;
            line-height: 1.6;
            margin: 0;
            padding: 0;
            background-color: #e2f3f5;
            overflow-x: hidden;
            transition: background-color 0.3s, color 0.3s;
        }
        .dark-mode {
            background-color: #333;
            color: #f0f0f0;
        }
        .portfolio {
            max-width: 800px;
            margin: auto;
            padding: 20px;
            background: #ffffff;
            border-radius: 10px;
            box-shadow: 0 4px 20px rgba(0, 0, 0, 0.1);
            animation: fadeIn 0.6s forwards; /* Animation on load */
        }
        @keyframes fadeIn {
            from { opacity: 0; transform: translateY(20px); }
            to { opacity: 1; transform: translateY(0); }
        }
        /* Navigation */
        .nav {
            display: flex;
            justify-content: space-between;
            padding: 10px;
            background: #007bff;
            color: white;
            border-radius: 10px;
        }
        .nav a {
            color: white;
            text-decoration: none;
            padding: 10px 15px;
        }
        .nav a:hover {
            background: #0056b3;
            border-radius: 5px;
        }
        .header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 20px;
            background: #007bff;
            color: white;
            padding: 10px;
            border-radius: 10px;
        }
        .header-name {
            margin: 0;
            font-size: 2.5em; /* Increased font size */
            transition: color 0.3s;
        }
        .header-name:hover {
            color: #ffe600; /* Color change on hover */
        }
        .header-contact {
            margin: 0;
        }
        .header-contact-item {
            margin: 5px 0;
        }
        .header-image {
            width: 120px; /* Increased image size */
            height: auto;
            border-radius: 50%;
            transition: transform 0.3s, box-shadow 0.3s;
        }
        .header-image:hover {
            transform: scale(1.1);
            box-shadow: 0 4px 15px rgba(0, 0, 0, 0.2);
        }
        .section {
            margin-bottom: 20px;
            padding: 10px;
            border-left: 4px solid #007bff;
            transition: background 0.3s, transform 0.3s;
        }
        .section-title {
            color: #007bff;
            font-size: 1.5em;
            margin-bottom: 10px;
        }
        .skills-list, .additional-info-list {
            list-style: none;
            padding: 0;
        }
        .skills-item, .additional-info-item {
            margin: 5px 0;
            padding: 5px;
            border-radius: 5px;
            background: #007bff;
            color: white;
            transition: background 0.3s, transform 0.3s;
        }
        .skills-item:hover, .additional-info-item:hover {
            background: #0056b3;
            transform: translateY(-2px); /* Slightly lift on hover */
        }
        .project-item {
            margin-bottom: 15px;
            padding: 10px;
            border-radius: 5px;
            background: #f7f7f7;
            transition: transform 0.3s, box-shadow 0.3s;
        }
        .project-item:hover {
            transform: translateY(-5px);
            box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1);
        }
        .testimonial-item {
            margin-bottom: 15px;
            padding: 10px;
            border-radius: 5px;
            background: #f9f9f9;
            transition: transform 0.3s;
        }
        .testimonial-item:hover {
            transform: translateY(-3px);
        }
        .download-button {
            background-color: #007bff;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            transition: background-color 0.3s, transform 0.3s;
            margin-top: 20px;
            font-size: 1.2em;
        }
        .download-button:hover {
            background-color: #0056b3;
            transform: scale(1.05); /* Scale up on hover */
        }
        /* Portfolio gallery */
        .gallery {
            display: flex;
            flex-wrap: wrap;
            gap: 10px;
        }
        .gallery-item {
            flex: 1 1 calc(30% - 10px); /* 3 items per row with spacing */
            border: 2px solid #007bff;
            border-radius: 5px;
            overflow: hidden;
            position: relative;
            transition: transform 0.3s;
        }
        .gallery-item img {
            width: 100%;
            height: auto;
            transition: transform 0.3s;
        }
        .gallery-item:hover {
            transform: scale(1.05); /* Slightly enlarge on hover */
        }
        .gallery-item:hover img {
            transform: scale(1.1); /* Zoom in image on hover */
        }
        /* Contact form */
        .contact-form {
            margin-top: 20px;
            background: #f9f9f9;
            padding: 20px;
            border-radius: 10px;
        }
        .contact-form input, .contact-form textarea {
            width: calc(100% - 20px);
            padding: 10px;
            margin: 10px 0;
            border: 1px solid #ccc;
            border-radius: 5px;
        }
        .contact-form button {
            background-color: #007bff;
            color: white;
            border: none;
            padding: 10px;
            border-radius: 5px;
            cursor: pointer;
            transition: background-color 0.3s;
        }
        .contact-form button:hover {
            background-color: #0056b3;
        }
    </style>
</head>
<body>
    <div class="portfolio">
        <nav class="nav">
            <a href="#summary">Summary</a>
            <a href="#education">Education</a>
            <a href="#skills">Skills</a>
            <a href="#projects">Projects</a>
            <a href="#testimonials">Testimonials</a>
            <a href="#blog">Blog</a>
            <a href="#contact">Contact</a>
            <button onclick="toggleDarkMode()">Toggle Dark Mode</button>
        </nav>
        
        <header class="header">
            <div class="header-left">
                <h1 class="header-name">Dharanish</h1>
                <div class="header-contact">
                    <p class="header-contact-item">Phone: xxxxxxxx</p>
                    <p class="header-contact-item">Email: <a href="mailto:xxxxxxxxx" style="color: white;">xxxxxxxxx</a></p>
                    <p class="header-contact-item">LinkedIn: <a href="https://www.linkedin.com/in/yourprofile" target="_blank" style="color: white;">xxxxxxxxxxx</a></p>
                    <p class="header-contact-item">Location: Coimbatore, India</p>
                </div>
            </div>
            <div class="header-right">
                <img src="img/about.jpg" alt="xxxx" class="header-image">
            </div>
        </header>
        
        <section class="section" id="summary">
            <h2 class="section-title">Summary</h2>
            <p>A passionate AI and Data Science student with hands-on experience in embedded systems and cybersecurity, seeking opportunities to apply my skills in real-world applications.</p>
        </section>

        <section class="section" id="education">
            <h2 class="section-title">xxx</h2>
            <ul class="education-list">
                <li class="education-item">B.Tech in Artificial Intelligence and Data Science (2021-2025) - KCT</li>
            </ul>
        </section>

        <section class="section" id="xxx">
            <h2 class="section-title">xx</h2>
            <div class="skills-list">
                <div class="skills-item">xxx (90%)</div>
                <div class="skills-item">xxxx (80%)</div>
                <div class="skills-item">xx(85%)</div>
                <div class="skills-item">Cybersecurity (75%)</div>
            </div>
        </section>

        <section class="section" id="projects">
            <h2 class="section-title">Projects</h2>
            <div class="section-content">
                <div class="project-item">
                    <h3 class="project-title">HOME AUTOMATION</h3>
                    <p class="project-details">Designed and deployed a comprehensive home automation solution using ESP32 microcontroller and MQTT protocol, enabling remote monitoring and control of household appliances through a custom-built mobile application.</p>
                </div>
                <div class="project-item">
                    <h3 class="project-title">WIFI JAMMER</h3>
                    <p class="project-details">Created a WiFi jammer project utilizing ESP8266 microcontroller, capable of transmitting deauthentication packets to disrupt WiFi network connections within its range.</p>
                </div>
            </div>
        </section>

        <section class="section" id="testimonials">
            <h2 class="section-title">Testimonials</h2>
            <div class="testimonial-item">
                <p>"xxxxxxxxxx"</p>
            </div>
            <div class="testimonial-item">
                <p>"xxxxxxxxxxxxxxxxxx"</p>
            </div>
        </section>

        <section class="section" id="blog">
            <h2 class="section-title">Blog</h2>
            <p>Coming soon! I plan to share my thoughts and insights on AI and Data Science.</p>
        </section>

        <section class="section" id="contact">
            <h2 class="section-title">Contact Me</h2>
            <form class="contact-form" onsubmit="sendMessage(event)">
                <input type="text" placeholder="Your Name" required>
                <input type="email" placeholder="Your Email" required>
                <textarea placeholder="Your Message" required></textarea>
                <button type="submit">Send Message</button>
            </form>
        </section>

        <section class="section">
            <h2 class="section-title">Portfolio Gallery</h2>
            <div class="gallery">
                <div class="gallery-item">
                    <img src="img/project1.jpg" alt="Project 1">
                </div>
                <div class="gallery-item">
                    <img src="img/project2.jpg" alt="Project 2">
                </div>
                <div class="gallery-item">
                    <img src="img/project3.jpg" alt="Project 3">
                </div>
            </div>
        </section>

        <section class="section">
            <h2 class="section-title">Additional Information</h2>
            <div class="section-content">
                <ul class="additional-info-list">
                    <li class="additional-info-item">Languages: English (Fluent), Other Language (Basic)</li>
                    <li class="additional-info-item">Volunteer Experience: xxxxxxxxxx</li>
                    <li class="additional-info-item">Interests: Make new projects and ideas using MCUs, Cyber Security.</li>
                </ul>
            </div>
        </section>
        
        <button class="download-button" onclick="window.open('/resume.pdf', '_blank');">Download PDF Resume</button>
    </div>

    <script>
        function toggleDarkMode() {
            document.body.classList.toggle('dark-mode');
        }

        function sendMessage(event) {
            event.preventDefault();
            alert("Your message has been sent!");
            // Here, you can implement the functionality to send the message
        }
    </script>
</body>
</html>
)rawliteral";

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", []() {
        server.send(200, "text/html", htmlContent);
    });

    server.begin();
}

void loop() {
    server.handleClient();
}