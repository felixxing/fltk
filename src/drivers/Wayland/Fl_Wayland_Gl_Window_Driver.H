//
// Class Fl_Wayland_Gl_Window_Driver for the Fast Light Tool Kit (FLTK).
//
// Copyright 2021-2022 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     https://www.fltk.org/COPYING.php
//
// Please see the following page on how to report bugs and issues:
//
//     https://www.fltk.org/bugs.php
//

#ifndef FL_WAYLAND_GL_WINDOW_DRIVER_H
#define FL_WAYLAND_GL_WINDOW_DRIVER_H

#include <config.h>
#if HAVE_GL
#include "../../Fl_Gl_Window_Driver.H"
#include <wayland-egl.h>
#include <EGL/egl.h>
#include <FL/gl.h>

/* Implementation note about OpenGL drawing on the Wayland platform

After eglCreateWindowSurface() with attributes {EGL_RENDER_BUFFER, EGL_SINGLE_BUFFER, EGL_NONE},
eglQueryContext() reports that EGL_RENDER_BUFFER equals EGL_BACK_BUFFER.
This experiment suggests that the platform only supports double-buffer drawing.
Consequently, FL_DOUBLE is enforced in all Fl_Gl_Window::mode_ values under Wayland.
*/

class Fl_Wayland_Gl_Window_Driver : public Fl_Gl_Window_Driver {
  friend Fl_Gl_Window_Driver* Fl_Gl_Window_Driver::newGlWindowDriver(Fl_Gl_Window *);
  friend class Fl_Wayland_Gl_Plugin;
private:
  static EGLDisplay egl_display;
  static EGLint configs_count;
  struct wl_egl_window *egl_window;
  EGLSurface egl_surface;
  bool egl_swap_in_progress;
  Fl_Wayland_Gl_Window_Driver(Fl_Gl_Window *win);
  float pixels_per_unit() FL_OVERRIDE;
  void make_current_before() FL_OVERRIDE;
  int mode_(int m, const int *a) FL_OVERRIDE;
  void swap_buffers() FL_OVERRIDE;
  void resize(int is_a_resize, int w, int h) FL_OVERRIDE;
  char swap_type() FL_OVERRIDE;
  Fl_Gl_Choice *find(int m, const int *alistp) FL_OVERRIDE;
  GLContext create_gl_context(Fl_Window* window, const Fl_Gl_Choice* g) FL_OVERRIDE;
  void set_gl_context(Fl_Window* w, GLContext context) FL_OVERRIDE;
  void delete_gl_context(GLContext) FL_OVERRIDE;
  void make_overlay_current() FL_OVERRIDE;
  void redraw_overlay() FL_OVERRIDE;
  void gl_start() FL_OVERRIDE;
  void gl_visual(Fl_Gl_Choice *c) FL_OVERRIDE;
  char *alpha_mask_for_string(const char *str, int n, int w, int h, Fl_Fontsize fs) FL_OVERRIDE;
  void init();
public:
  //virtual bool need_scissor() { return true; } // CONTROL_LEAKING_SUB_GL_WINDOWS
  //void apply_scissor(); // CONTROL_LEAKING_SUB_GL_WINDOWS
};

#endif // HAVE_GL
#endif // FL_WAYLAND_GL_WINDOW_DRIVER_H
