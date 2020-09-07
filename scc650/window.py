import glfw
from OpenGL.GL import *
import OpenGL.GL.shaders

glfw.init()

glfw.window_hint(glfw.VISIBLE, glfw.FALSE)
window = glfw.create_window(720, 600, "My first window :)", None, None)

if not window:
    glfw.terminate()

glfw.make_context_current(window)

while not glfw.window_should_close(window):
    glfw.poll_events()

    glfw.swap_buffers(window)

glfw.terminate()
