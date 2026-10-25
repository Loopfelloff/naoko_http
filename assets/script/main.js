/* main.js: nav toggle, sakura petals, copy buttons, 404 path readout */
(function () {
  "use strict";

  // Mobile nav toggle
  var toggle = document.querySelector(".nav-toggle");
  var nav = document.getElementById("site-nav");
  if (toggle && nav) {
    toggle.addEventListener("click", function () {
      var open = nav.classList.toggle("is-open");
      toggle.setAttribute("aria-expanded", String(open));
    });
  }

  // Copy buttons on code blocks
  document.querySelectorAll("[data-copy]").forEach(function (btn) {
    btn.addEventListener("click", function () {
      var target = document.getElementById(btn.getAttribute("data-copy"));
      if (!target || !navigator.clipboard) return;
      navigator.clipboard.writeText(target.textContent.trim()).then(function () {
        var old = btn.textContent;
        btn.textContent = "Copied";
        setTimeout(function () { btn.textContent = old; }, 1500);
      });
    });
  });

  // Show the missing path on the 404 page
  var missing = document.getElementById("missing-path");
  if (missing) missing.textContent = window.location.pathname;

  // Sakura petals: skipped when the visitor prefers reduced motion
  var canvas = document.getElementById("petals");
  if (!canvas || window.matchMedia("(prefers-reduced-motion: reduce)").matches) return;

  var ctx = canvas.getContext("2d");
  var petals = [];
  var w = 0, h = 0, running = true;

  function resize() {
    var dpr = window.devicePixelRatio || 1;
    w = window.innerWidth; h = window.innerHeight;
    canvas.width = w * dpr; canvas.height = h * dpr;
    ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
  }

  function spawn(initial) {
    return {
      x: Math.random() * w,
      y: initial ? Math.random() * h : -20,
      size: 6 + Math.random() * 8,
      speed: 0.5 + Math.random() * 0.9,
      drift: 0.3 + Math.random() * 0.6,
      phase: Math.random() * Math.PI * 2,
      rot: Math.random() * Math.PI * 2,
      spin: (Math.random() - 0.5) * 0.03,
      alpha: 0.35 + Math.random() * 0.4
    };
  }

  function init() {
    resize();
    petals = [];
    var count = Math.min(30, Math.round(w / 45));
    for (var i = 0; i < count; i++) petals.push(spawn(true));
  }

  function draw() {
    if (!running) return;
    ctx.clearRect(0, 0, w, h);
    petals.forEach(function (p, i) {
      p.y += p.speed;
      p.phase += 0.02;
      p.x += Math.sin(p.phase) * p.drift;
      p.rot += p.spin;
      if (p.y > h + 20) petals[i] = spawn(false);
      ctx.save();
      ctx.translate(p.x, p.y);
      ctx.rotate(p.rot);
      ctx.globalAlpha = p.alpha;
      ctx.fillStyle = "#ff8fb8";
      ctx.beginPath();
      ctx.ellipse(0, 0, p.size, p.size * 0.55, 0, 0, Math.PI * 2);
      ctx.fill();
      ctx.restore();
    });
    requestAnimationFrame(draw);
  }

  document.addEventListener("visibilitychange", function () {
    running = !document.hidden;
    if (running) requestAnimationFrame(draw);
  });
  window.addEventListener("resize", init);
  init();
  requestAnimationFrame(draw);
})();
