require "bundler"
Bundler.require(:default)

require "rack/jekyll"
run Rack::Jekyll.new
