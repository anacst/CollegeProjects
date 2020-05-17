import numpy as np
import imageio

def DFT2D(f):
    # create empty array of complex coefficients
    F = np.zeros(f.shape, dtype=np.complex64)
    n,m = f.shape[0:2]
    
    # creating indices for x, to compute multiplication using numpy (f*exp)
    x = np.arange(n)
    # for each frequency 'u,v'
    for u in np.arange(n):
        for v in np.arange(m):
            for y in np.arange(m):
                F[u,v] += np.sum(f[:,y] * np.exp( (1j*2*np.pi) * (((u*x)/n)+((v*y)/m)) ))
                
    return F/np.sqrt(n*m)

def IDFT2D(f):
    # create empty array of complex coefficients
    F = np.zeros(f.shape, dtype=np.complex64)
    n,m = f.shape[0:2]
    
    # creating indices for x, to compute multiplication using numpy (f*exp)
    x = np.arange(n)
    # for each frequency 'u,v'
    for u in np.arange(n):
        for v in np.arange(m):
            for y in np.arange(m):
                F[u,v] += np.sum(f[:,y] * np.exp( (1j*2*np.pi) * (((u*x)/n)+((v*y)/m)) ))
                
    return F/np.sqrt(n*m)


# parameters input
filename = str(input()).strip()
img = imageio.imread(filename)
T = float(input())

n,m = img.shape

# compute fourier transform of the image
F = np.fft.fft2(img)/np.sqrt(n*m)

# finding maximum coefficient (not counting the [0,0])
p2 = np.abs(F[0,1])
for i in np.arange(n):
    for j in np.arange(m):
        if (np.abs(F[i,j]) != np.abs(F[0,0]) and np.abs(F[i,j]) > p2):
            p2 = np.abs(F[i,j])

t = p2*T
nCoefficients = 0
for i in np.arange(n):
    for j in np.arange(m):
        if (np.abs(F[i,j]) < t):
            F[i,j] = 0
            nCoefficients = nCoefficients + 1

# computing inverse fourier transform
IF = IDFT2D(F)

mean = np.sum(img)/(n*m)
new_mean = np.sum(np.abs(IF))/(n*m)

print("Threshold=%.4f" % t) 
print("Filtered Coefficients=%d" % nCoefficients)
print("Original Mean=%.2f" % mean)
print("New Mean=%.2f" %  new_mean)
