// webpack.mix.js

let mix = require('laravel-mix');

require('mix-tailwindcss');

mix.sass('src/resources/sass/index.scss', 'data/css')
   .tailwind();

mix.browserSync({
  files: ["src/resources/**/*.js", "src/resources/**/*.css", "data/**/*.html"],
  server: {
    baseDir: "data",
    index: "index.html"
  }
});
