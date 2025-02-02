<script>
    import { Link } from "svelte-routing";
    import Nav from "./Nav.svelte";
    import HomeIcon from "./assets/house-chimney.svg";
    import Sensor from "./assets/sensor-on.svg";

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
        console.log(message.toString());
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
