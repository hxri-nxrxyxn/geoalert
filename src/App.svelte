<script>
    import { Router, Route } from "svelte-routing";
    import Home from "./Home.svelte";
    import Stats from "./Stats.svelte";
</script>

<main>
    <Router>
        <Route path="/" component={Home} />
        <Route path="/stats" component={Stats} />
    </Router>
</main>

<style>
    main {
        padding: 2rem;
    }
</style>
