<script>
    import Nav from "./Nav.svelte";
    import HomeIcon from "./assets/house-chimney.svg";
    import Sensor from "./assets/sensor-on.svg";
    import { Link } from "svelte-routing";

    let vibration = "NO";
    let state = $state("safe");

    import mqtt from "mqtt";
    const client = mqtt.connect("mqtt://test.mosquitto.org:8080");

    client.on("connect", () => {
        console.log("Connected to MQTT broker");
        client.subscribe("geo_alert/sensors", (err) => {
            if (!err) {
                console.log("Subscribed to geo_alert/sensors");
            }
        });
    });

    client.on("message", (topic, message) => {
        try {
            const data = JSON.parse(message.toString());
            vibration = data.vibration || "NO";
            if (vibration == "YES") {
                state = "unsafe";
                document.querySelector(".status__text").style.borderColor =
                    "#d63031";
            }
        } catch (error) {
            console.error("Error parsing JSON:", error);
            console.error("Raw message:", message.toString());
        }
    });
</script>

<main>
    <Nav />
    <div class="status">
        <div class="status__text">
            <h1>{state}</h1>
        </div>
    </div>
    <p>
        {state == "unsafe" ? `` : `No`} Landslide has been <b>reported</b>
    </p>
</main>
<div class="foot">
    <img src={HomeIcon} class="super home" alt="sensor" />
    <Link to="/stats">
        <img src={Sensor} alt="sensor" />
    </Link>
</div>

<style>
    .status {
        margin-top: 5rem;
        height: 40vh;
    }
    .status__text {
        margin-inline: auto;
        display: flex;
        justify-content: center;
        align-items: center;
        height: 60vw;
        width: 60vw;
        border-radius: 50%;
        border: 2px solid #00b894;
    }
    .status__text h1 {
        font-size: 1rem;
        text-transform: uppercase;
    }
    p {
        font-size: 0.75rem;
        margin-top: 5rem;
    }
    p b {
        font-weight: 700;
    }
</style>
