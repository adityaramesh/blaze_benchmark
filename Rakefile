require 'rake/clean'

cxx       = ENV['CXX']
boost     = ENV['BOOST_INCLUDE_PATH']
eigen3    = ENV['EIGEN3_INCLUDE_PATH']
langflags = "-std=c++11"
wflags    = "-Wall"
archflags = "-march=native"
incflags  = "-I. -isystem #{boost} -isystem #{eigen3} -isystem include/blaze-2.4"
ppflags   = "-DNDEBUG -DEIGEN_DONT_VECTORIZE"
optflags  = "-O3"
cxxflags  = "#{langflags} #{wflags} #{archflags} #{incflags} #{ppflags} #{optflags}"
tests     = FileList["src/*"].map{|f| f.sub("src", "out").ext("run")}

task :default => tests

task :out do
	unless File.directory?("out")
		sh "mkdir out"
	end
end

tests.each do |f|
	file f => :out do
		sh "#{cxx} #{cxxflags} -o #{f} #{f.sub('out', 'src').ext('cpp')}"
	end
end

task :clobber => :out do
	sh "rm -rf out/*"
end
