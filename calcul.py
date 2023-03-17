import numpy 
l0 = 2e-2     
delta = 2.5e-2
h = 3.0e-2
w0 = 0.2       
dt = 0.5       
gamma = 15.8e-6
m = 8e-3          
J = m * h * h / 3
g = 9.8         
k = 20.0      





b = (2 * 0.19 - (1 - gamma * dt / (2 * J)) * 0.1 + 3 * g * dt * dt / (2 * h) * numpy.sin(0.19) - dt * dt * k * h * (1 / (2 * J)) * (l0 - 0.0196)) / (1 +gamma * dt /(2 * J))
print(b)