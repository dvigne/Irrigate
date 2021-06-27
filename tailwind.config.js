module.exports = {
  purge: {
    // mode: 'all',
    content: [
    'data/**/*.html',
    'data/**/*.js'
  ],
  safelist: [
    /data-theme$/,
  ]
  },
  darkMode: false, // or 'media' or 'class'
  theme: {
    extend: {},
  },
  variants: {
    extend: {},
  },
  plugins: [
    require('daisyui'),
  ],
}
