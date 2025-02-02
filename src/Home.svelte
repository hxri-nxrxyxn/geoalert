<script>
    import Nav from "./Nav.svelte";
    import HomeIcon from "./assets/house-chimney.svg";
    import Sensor from "./assets/sensor-on.svg";
    import { Link } from "svelte-routing";
</script>

<main>
    <Nav />
    <div class="status">
        <div class="status__text">
            <h1>SAFE</h1>
        </div>
    </div>
    <p>No landslide has been reported from <b>Kozhikode</b></p>
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
    }
    p {
        font-size: 0.75rem;
        margin-top: 5rem;
    }
    p b {
        font-weight: 700;
    }
</style>
