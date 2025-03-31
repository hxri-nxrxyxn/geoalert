<script>
    import Nav from "./Nav.svelte";
    import HomeIcon from "./assets/house-chimney.svg";
    import Sensor from "./assets/sensor-on.svg";
    import { Link } from "svelte-routing";
    import { initializeApp } from "firebase/app";
    import { getDatabase, ref, onValue } from "firebase/database";

    // State variables using Svelte 5's $state
    let vibration = "NO";
    let state = $state("safe");

    // Firebase configuration
    const firebaseConfig = {
        apiKey: "AIzaSyCLbiKPaJ36j--ZGGa0kgqIdt-TZfpFIdI",
        authDomain: "loraalert-72e69.firebaseapp.com",
        databaseURL:
            "https://loraalert-72e69-default-rtdb.asia-southeast1.firebasedatabase.app",
        projectId: "loraalert-72e69",
        storageBucket: "loraalert-72e69.firebasestorage.app",
        messagingSenderId: "194512426008",
        appId: "1:194512426008:web:29571e0afcbaf8c5a91f6d",
        measurementId: "G-VYWDN4MEF1",
    };

    // Initialize Firebase
    const app = initializeApp(firebaseConfig);
    const database = getDatabase(app);

    // Reference to the sensors data
    const sensorsRef = ref(database, "geo_alert/sensors");

    // Listen for changes in the sensors data
    onValue(sensorsRef, (snapshot) => {
        try {
            const data = snapshot.val();
            if (data) {
                console.log(data);
                vibration = data.vibration || "NO";
                if (vibration === "YES") {
                    state = "unsafe";
                    document.querySelector(".status__text").style.borderColor =
                        "#d63031";
                } else {
                  state = "safe";
                  document.querySelector(".status__text").style.borderColor =
                      "#00b894";
                }
            }
        } catch (error) {
            console.error("Error reading data:", error);
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
        {state === "unsafe" ? `` : `No`} Landslide has been <b>reported</b>
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
