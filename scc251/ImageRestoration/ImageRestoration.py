from scipy.fftpack import fftn, ifftn, fftshift
import numpy as np
import imageio

def gaussian_filter(k=3, sigma=1.0):
    arx = np.arange((-k // 2) + 1.0, (k // 2) + 1.0)
    x, y = np.meshgrid(arx, arx)
    filt = np.exp( -(1/2)*(np.square(x) + np.square(y))/np.square(sigma) )
    return filt/np.sum(filt)

#def image_normalization(f):
#   return (255 * (f - f.min())/(f.max() - f.min())

# parameters input
filename = str(input()).strip()
k = int(input())
sigma = float(input())
gamma = float(input())

img = imageio.imread(filename)
h = gaussian_filter(k, sigma)

# padding image to multiply  
a = int(img.shape[0]//2 - h.shape[0]//2) 
h_pad = np.pad(h, (a,a-1), 'constant', constant_values=(0))

G = fftn(img)
H = fftn(h_pad)

# image denoising 
denoised_img = np.multiply(G, H)

# normalizing image
denoised_img = 255 * (denoised_img - denoised_img.min()) / (denoised_img.max() - denoised_img.min())

output_img = ifftn(denoised_img)
imageio.imwrite("denoiused_img_b1_n.png", output_img)
