import numpy as np
import imageio
from skimage import morphology

def openingRGB(img, k):
    new_img = np.zeros(img.shape, dtype='float')
    new_img[:,:,0] = morphology.opening(img[:,:,0], morphology.disk(k)).astype(np.uint8)
    new_img[:,:,1] = morphology.opening(img[:,:,1], morphology.disk(k)).astype(np.uint8)
    new_img[:,:,2] = morphology.closing(img[:,:,2], morphology.disk(k)).astype(np.uint8)
    return new_img.astype(np.uint8)

def gradient(img, k):
    img_hsv = mpl.colors.rgb_to_hsv(img)
    img_hsv[:,:,0] = normalize(img_hsv[:,:,0])
    
    new_img[:,:,0] = morphology.dilation(img_hsv[:,:,0], morphology.disk(k)).astype(np.uint8) - morphology.erosion(img_hsv[:,:,0], morphology.disk(k)).astype(np.uint8)
    new_img[:,:,1] = morphology.opening(img_hsv[:,:,0], morphology.disk(k)).astype(np.uint8)
    new_img[:,:,2] = morphology.closing(img_hsv[:,:,0], morphology.disk(k)).astype(np.uint8)

    return  new_img

def normalize(f):
    return ((f - f.min()) * 255) / f.max() - f.min()

def error(f, r):
    """Computing error from image reference to processed image"""
    n, m, k = f.shape
    return np.sqrt(np.sum(np.square(np.subtract(f.astype(np.float64), r.astype(np.float64))))/(n*m))

def main():
	filename = str(input()).strip()
	size = int(input())
	option = int(input())

	img = imageio.imread(filename)

	if option == 1:
		out = openingRGB(img, size)

	if option == 2:
		out = gradient(img, size)

	if option == 3:
		aux = openingRGB(img, 2*size)
		out = gradient(aux, size)
    
	print('%.4f' % error(out, img))

if __name__ == '__main__':
	main()