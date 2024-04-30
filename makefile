pipeline: pipeline.cc ImageReader.o ImageQueue.o ImageSmoother.o GaussianNoiseInjector.o ImageNormalizer.o ImageWriter.o
	u++ -o pipeline ImageReader.o ImageQueue.o ImageSmoother.o GaussianNoiseInjector.o ImageNormalizer.o ImageWriter.o pipeline.cc -lcfitsio

ImageQueue.o: ImageQueue.cc ImageQueue.h
	u++ -c ImageQueue.cc

ImageReader.o: ImageReader.cc ImageReader.h
	u++ -c ImageReader.cc 

ImageSmoother.o: ImageSmoother.cc ImageSmoother.h
	u++ -c ImageSmoother.cc

GaussianNoiseInjector.o: GaussianNoiseInjector.cc GaussianNoiseInjector.h
	u++ -c GaussianNoiseInjector.cc

ImageNormalizer.o: ImageNormalizer.cc ImageNormalizer.h
	u++ -c ImageNormalizer.cc

ImageWriter.o: ImageWriter.cc ImageWriter.h
	u++ -c ImageWriter.cc

clean:
	rm -f pipeline *.o

clean_out_images:
	rm -f *out[0-9].fits
