<template>
  <div>
    <header>
      <div>
        <b-navbar type="dark" variant="info">
          <b-navbar-brand> Underground Oil Tank Monitor System</b-navbar-brand>
        </b-navbar>
      </div>
    </header>
    <body style="margin-top: 2em; margin-left: 5em; margin-right: 5em">
      <div>
        <div class="row">
          <div v-for="name in names" :key="name" class="col-4">
            <b-card style="margin-top = 5em; max-width: 20em">
              <p>
                Hello, I'm a card, user me for all your meow meow needs
                {{ name }}
              </p>
              <b-card-text>Hello World</b-card-text>
            </b-card>
          </div>
        </div>
        <div style="margin-top: 2em">
          <p>Oil Log</p>
          <div>
            <b-table striped hover :items="items"></b-table>
          </div>
        </div>
      </div>
    </body>
  </div>
</template>

<script>
export default {
  props: {},
  data() {
    return {
      names: ["oil level", "oil temperature", "Decision"],
      level: [56.343, 53.34, 48.09, 30.0, 19.46, 9.93],
      temp: [32.2, 32.6, 32.1, 30.89, 45.23, 80.34],
      alert: ["Oil level decreasing too fast", "Oil temperature too high"],
      items: [
        { age: 40, first_name: "Dickerson", last_name: "Macdonald" },
        { age: 21, first_name: "Larsen", last_name: "Shaw" },
        { age: 89, first_name: "Geneva", last_name: "Wilson" },
        { age: 38, first_name: "Jami", last_name: "Carney" },
      ],
    };
  },
};
</script>
