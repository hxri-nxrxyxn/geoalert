<script>
    import { Router, Route } from "svelte-routing";
    import Home from "./Home.svelte";
    import Stats from "./Stats.svelte";
</script>

<main>
    <Router>
        <Route to="/" component={Home} />
        <Route to="/stats" component={Stats} />
    </Router>
</main>

<style></style>
