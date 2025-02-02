<script>
    import { Link } from "svelte-routing";
    import Nav from "./Nav.svelte";
    import HomeIcon from "./assets/house-chimney.svg";
    import Sensor from "./assets/sensor-on.svg";
    import * as Paho from "paho-mqtt";

    // Create a client instance: Broker, Port, Websocket Path, Client ID
    let client = new Paho.MQTT.Client(
        "broker.hivemq.com",
        Number(80),
        "/geo_alert/sensors",
        "clientId_AIPH0X0qFf",
    );

    let accelerometerX = 0.0;
    let accelerometerY = 0.0;
    let accelerometerZ = 0.0;
    let pressure = 0.0;
    let relativePressure = 0.0;
    let altitude = 0.0;

    client.onConnectionLost = function (responseObject) {
        console.log("Connection Lost: " + responseObject.errorMessage);
    };

    console.log("hey");

    client.onMessageArrived = function (message) {
        console.log("Message Arrived: " + message.payloadString);

        try {
            // Attempt to parse the message as JSON.  Adjust this to your actual message format.
            const payload = JSON.parse(message.payloadString);

            // Example assuming your JSON payload looks like this:
            // { "accelerometer": { "x": 0.5, "y": -0.2, "z": 0.8 }, "pressure": 1013.2, ... }

            if (payload.accelerometer) {
                accelerometerX = payload.accelerometer.x;
                accelerometerY = payload.accelerometer.y;
                accelerometerZ = payload.accelerometer.z;
            }
            if (payload.pressure) {
                pressure = payload.pressure;
            }
            if (payload.relativePressure) {
                relativePressure = payload.relativePressure;
            }
            if (payload.altitude) {
                altitude = payload.altitude;
            }
        } catch (error) {
            console.error("Error parsing JSON:", error);
            // Handle the error appropriately, e.g., display an error message.
        }
    };

    function onConnect() {
        console.log("Connected");
        // Subscribe to the topic after connecting
        client.subscribe("/geo_alert/sensors"); // Or the specific topic you need
    }

    client.connect({
        onSuccess: onConnect,
    });
</script>

<main>
    <Nav />
    <div class="stats">
        <div class="stat">
            <div class="stat__title">
                <h1>Accelerometer <span>X Y Z</span></h1>
            </div>
            <div class="stat__tiles">
                <div class="stat__tile">
                    <h3>0.11</h3>
                </div>
                <div class="stat__tile">
                    <h3>0.11</h3>
                </div>
                <div class="stat__tile">
                    <h3>0.11</h3>
                </div>
            </div>
        </div>
        <div class="stat">
            <div class="stat__title">
                <h1>Pressure <span>mb</span></h1>
            </div>
            <div class="stat__tiles">
                <div class="stat__tile">
                    <h3>0.11</h3>
                </div>
            </div>
        </div>
        <div class="stat">
            <div class="stat__title">
                <h1>Relative Pressure <span>mb</span></h1>
            </div>
            <div class="stat__tiles">
                <div class="stat__tile">
                    <h3>0.11</h3>
                </div>
            </div>
        </div>
        <div class="stat">
            <div class="stat__title">
                <h1>Altitude <span>m</span></h1>
            </div>
            <div class="stat__tiles">
                <div class="stat__tile">
                    <h3>0.11</h3>
                </div>
            </div>
        </div>
    </div>

    <div class="foot">
        <Link to="/">
            <img src={HomeIcon} class="home" alt="sensor" />
        </Link>
        <img src={Sensor} class="super" alt="sensor" />
    </div>
</main>

<style>
    .stat {
        margin-top: 2rem;
    }
    .stat__title h1 {
        font-size: 0.75rem;
    }
    .stat__title h1 span {
        color: #00b894;
    }
    .stat__tiles {
        display: flex;
        justify-content: space-between;
        margin-top: 1rem;
    }
    .stat__tile {
        background: #111111aa;
        width: 30%;
        padding-block: 1rem;
    }
    .stat__tile h3 {
        font-size: 1rem;
        text-align: center;
    }
</style>
