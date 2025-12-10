#import "all.h"
#import "ring.h"
#import "test.h"

struct app_t : top_t {
  bool                           running   = true;
  bool                           reloading = false;
  map<shortcut_t, fun_t<void()>> shortcuts = {};

  app_t(int argc, char** argv) {
    rmr.cfg("base", "/Users/rodarmor/src/blaster/");
    run_tests();

    vector<string> raw_args{argv, argv + argc};
    vector<string> opt_args = raw_args;
    opt_args[0] = rmr.cfg("base") + "bin/opt";
    string help_text = rmr.slurp(rmr.cfg("base") + "help.txt");
    string json_args = rmr.run(opt_args[0], opt_args, help_text);
    val_t  args      = val_t::parse(json_args);

    if (args.is_null()) {
      rmr.die("app: bad command line: %"_fmt(rmr.join(raw_args, " ")));
    }

    int width   = rmr.stoi(args.get("--width" ).str());
    int height  = rmr.stoi(args.get("--height").str());

    if ((bool)args.get("--verbose")) rmr.loglevel_info();

    if (args.get("--resolution")) {
      string r = args.get("--resolution").str();
      if      (r == "1800p") { width = 2880; height = 1800;               }
      else if (r == "1080p") { width = 1920; height = 1080;               }
      else if (r == "720p" ) { width = 1280; height =  720;               }
      else if (r == "480p" ) { width = 854;  height =  480;               }
      else if (r == "360p" ) { width = 640;  height =  360;               }
      else if (r == "240p" ) { width = 426;  height =  240;               }
      else if (r == "xga"  ) { width = 1024; height =  768;               }
      else if (r == "debug") { width = 1150; height = 1100;               }
      else                   { rmr.die("main: bad resolution: %"_fmt(r)); }
    }

    string route = args.get("--route").str();
    string id    = args.get("--id") ? args.get("--id").str() : rmr.uuid(4);
    //string title = "無心 - %"_fmt(id);
    string title = "BLASTER";

    auto& s = spawn<space_t>();

    auto& hints = s.hints();
    hints.width   = width;
    hints.height  = height;
    hints.hidden  = (bool)args.get("--background");
    hints.top     = rmr.stoi(args.get("--top"   ).str());
    hints.left    = rmr.stoi(args.get("--left"  ).str());
    hints.title   = title;

    auto& w = s.spawn_window();

    view_t* current = nullptr;

    for (auto& r : routes) {
      if (r.path() == route) {
        rmr.info("app: loading initial route: %"_fmt(r.path()));
        route_t::args_t a = {};
        for (auto& param : r.params()) {
          string flag = "--"s + param;
          a[param] = args.get(flag).str();
        }

        current = &r(w, a);
        break;
      }
    }

    if (!current) {
      rmr.die("app: couldn't load initial route: %"_fmt(route));
    }

    ring_t<double, 60> frame_times{};

    auto& overlay = w.spawn<grid_v>(30, 30);

    overlay
    .foreground("white"_color)
    .background("black"_color)
    .hide()
    ;

    on("super-j",     [&] { rmr.run("j build"); rmr.exec(*argv, argv); });
    on("super-s",     [&] { screenshot(w);                             });
    on("super-r",     [&] { reloading = true; w.gl().reload_prgs();    });
    on("super-enter", [&] { w.beat();                                  });
    on("super-o",     [&] { overlay.toggle();                          });

    for (tick_e tick; running; tick++) {
      broadcast(verify_e());
      broadcast(tick);
      broadcast(render_e(tick));

      if (!tick.first()) {
        frame_times.write(tick.elapsed());
        overlay.clear().set(0, 0, 1.0, 0.25, "%ms"_fmt(rmr.ms(rmr.mean(frame_times))));
      }

      rmr.spam("frame %: %ms %"_fmt(tick.count, rmr.ms(tick.elapsed()), rmr.format_bytes(rmr.heap_size())));
      if (tick.first()) screenshot(w);
    }
  }

  void operator()(const character_e& e) override {
    // todo: only broadcast to focused view
    for (auto &child : *this) {
      child.broadcast(e);
    }
  }

  void operator()(const keydown_e& e) override {
    auto s = shortcut_t(e);
    if (shortcuts.count(s) > 0) shortcuts[s]();
    else {
      for (auto &child : *this) {
        // todo: only broadcast to focused view
        child.broadcast(e);
      }
    }
  }

  void operator()(const quit_e&) override {
    running = false;
  }

  void operator()(const tick_e& tick) override {
    if (reloading) {
      rmr << "main: reloaded";
      reloading = false;
    }
  }

  operator int() const {
    return 0;
  }

  void on(const string& str, fun_t<void()> handler) {
    auto s = shortcut_t(str);
    shortcuts[s] = handler;
  }

  void screenshot(window_t& w) {
    string dir = rmr.cfg("base") + "dat/screens";

    if (rmr.is_dir(dir)) {
      string filename = dir + "/%.%.png"_fmt(rmr.ms(), rmr.git_head());
      write_png(filename.c_str(), w.screenshot());
    } else {
      rmr << "app: dat/screens directory does not exist";
    }
  }
};
