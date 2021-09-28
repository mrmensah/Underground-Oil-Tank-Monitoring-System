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
          <div class="col-4">
            <b-card style="margin-top = 5em; max-width: 20em">
              <p>{{ this.names[0] }} : {{ this.levels[0]}}</p>
              <b-card-text>Hello World</b-card-text>
            </b-card>
          </div>
          <div class="col-4">
            <b-card style="margin-top = 5em; max-width: 20em">
              <p>{{ this.names[1] }} : {{ this.temp[0] }}</p>
              <b-card-text>Hello World</b-card-text>
            </b-card>
          </div>
          <div class="col-4">
            <b-card style="margin-top = 5em; max-width: 20em">
              <p>{{ this.names[2] }} : {{ this.alert[0] }}</p>
              <b-card-text>Hello World</b-card-text>
            </b-card>
          </div>
        </div>
        <div style="margin-top: 2em">
          <p>Oil Log</p>
          <div>
            <b-table
              id="my-table"
              :current-page="currentPage"
              :per-page="perPage"
              striped
              hover
              :items="tmp"
            ></b-table>
            <b-pagination
              v-model="currentPage"
              :total-rows="rows"
              :per-page="perPage"
              aria-controls="my-table"
            ></b-pagination>
            <p class="mt-3">Current Page: {{ currentPage }}</p>
          </div>
        </div>
      </div>
    </body>
  </div>
</template>

<script>
export default {
  data() {
    return {
      names: ["oil level", "oil temperature", "Decision"],
      levels: [56.343, 53.34, 48.09, 30.0, 19.46, 9.93],
      temp: [32.2, 32.6, 32.1, 30.89, 45.23, 80.34],
      alert: ["Oil level decreasing too fast", "Oil temperature too high"],
      sensors_data: [],
      perPage: 10,
      currentPage: 1,
      final_data: [],
      tmp: [],
    };
  },
  computed: {
    // reversedSensorsData: function () {
    //   this.sensors_data = this.sensors_data.reverse();
    //   return this.sensors_data;
    // },
    rows() {
      return this.tmp.length;
    },
  },
  activated() {
    // Call fetch again if last fetch more than 30 sec ago
    if (this.$fetchState.timestamp <= Date.now() - 30000) {
      this.$fetch();
    }
  },
  async fetch() {
    this.tmp = await fetch("http://0.0.0.0:8000/data/").then((res) =>
      res.json()
    );
    this.sensors_data = this.tmp;
    console.log("This is the data : ", this.tmp);
  },
  methods: {
    reverseData: function () {
      this.final_data = this.sensors_data.reverse();
      console.log("This data is reversed: ",this.final_data);
    },
  },
  // beforeCreate() {
  //   setTimeout(this.reverseData, 2000);
  // },
  mounted() {
    setTimeout(this.reverseData, 2000);
    //print out the level and temperature of the last data addition
    
  },
  //  updated() {
  //   setTimeout(this.reverseData, 0);
  // },
};
</script>
