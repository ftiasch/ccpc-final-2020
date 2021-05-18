# frozen_string_literal: true

$sample_count = 0
$test_count = 0
$targets = {}

file 'Rakefile'
directory 'aux'
directory 'samples'
directory 'tests'

def find(symbol)
  Dir["#{symbol}.{cc,cpp,java,py,rb}"].first.split('.')
end

def command(symbol)
  b, e = find(symbol)
  case e
  when 'cc'
    "./#{b}.exe"
  when 'cpp'
    "./#{b}.exe"
  when 'java'
    "java #{b}"
  when 'py'
    "python3 #{b}.py"
  when 'rb'
    "ruby #{b}.rb"
  end
end

def make_target(symbol)
  b, e = find(symbol)
  case e
  when 'cc'
    target = "#{b}.exe"
    file target => "#{b}.cc" do
      sh "clang-format -i #{b}.cc || true"
      sh "c++ -I../.. -Ofast -std=c++11 #{b}.cc -o#{b}.exe"
    end
  when 'cpp'
    target = "#{b}.exe"
    file target => "#{b}.cpp" do
      sh "clang-format -i #{b}.cpp || true"
      sh "c++ -I../.. -Ofast -std=c++11 #{b}.cpp -o#{b}.exe"
    end
  when 'java'
    target = "#{b}.class"
    file target => "#{b}.java" do
      sh "javac #{b}.java"
    end
  when 'py'
    target = "#{b}.py"
    file target
  when 'rb'
    target = "#{b}.rb"
    file target
  end
  target
end

def target(symbol)
  $targets[symbol] ||= make_target(symbol)
end

def add_target(symbol)
  task default: target(symbol)
end

def generate(generator, test_input, test_output, *params, **options)
  common_deps = %w[Rakefile aux samples tests]
  if generator.is_a? String
    file test_input => [*common_deps, generator] do
      cp generator, test_input
    end
  else
    seed_param = if options.key? :seed
                   options.delete(:seed)
                 else
                   test_input
                 end
    kw_params = options.map { |k, v| "-#{k} #{v}" }.join(' ')
    file test_input => [*common_deps, target(generator)] do
      sh "#{command generator} #{params.join(' ')} #{kw_params} #{seed_param} > #{test_input}"
    end
  end

  file test_output => [*common_deps, test_input, target(:check), target(:solution), target(:validator)] do
    sh "#{command :validator} < #{test_input}"
    sh "#{command :solution} < #{test_input} > #{test_output}"
    sh "bash -c '#{command :check} #{test_input} #{test_output} /tmp < #{test_output} 2>/dev/null; test $? -eq 42'"
  end
end

def sample(generator, *params, **options)
  $sample_count += 1

  test_input = format('samples/%03d', $sample_count)
  test_output = format('samples/%03d.a', $sample_count)

  generate generator, test_input, test_output, *params, **options
  task default: test_output
end

def test(generator, *params, **options)
  $test_count += 1

  test_input = format('tests/%03d', $test_count)
  test_output = format('tests/%03d.a', $test_count)

  generate generator, test_input, test_output, *params, **options
  task default: test_output
end

def multitest(*tests)
  $test_count += 1

  aux_inputs = []
  aux_outputs = []
  tests.each_with_index do |test, test_id|
    generator, *params = test
    options = {}
    options = params.pop if !params.empty? && params[-1].is_a?(Hash)
    aux_input = format('aux/%03d.%03d', $test_count, test_id)
    aux_output = format('aux/%03d.%03d.a', $test_count, test_id)
    generate generator, aux_input, aux_output, *params, **options
    aux_inputs << aux_input
    aux_outputs << aux_output
  end

  test_input = format('tests/%03d', $test_count)
  test_output = format('tests/%03d.a', $test_count)

  file test_input => aux_inputs do
    sh "cat #{aux_inputs.join(' ')} > #{test_input}"
  end
  file test_output => [test_input, *aux_outputs] do
    sh "#{command :validator} < #{test_input}"
    sh "#{command :solution} < #{test_input} > #{test_output}"
    sh "bash -c '#{command :check} #{test_input} #{test_output} <(cat #{aux_outputs.join(' ')})'"
  end

  task default: test_output
end

def packed
  yield

  packed_input = 'tests/test.in'
  packed_output = 'tests/test.out'
  inputs = []
  outputs = []
  1.upto($sample_count) do |i|
    inputs << format('samples/%03d', i)
    outputs << format('samples/%03d.a', i)
  end
  1.upto($test_count) do |i|
    inputs << format('tests/%03d', i)
    outputs << format('tests/%03d.a', i)
  end

  file packed_input => inputs + [target(:validator)] do
    sh "cat #{inputs.join(' ')} > #{packed_input}"
    sh "#{command :validator} < #{packed_input}"
  end
  file packed_output => [packed_input, *outputs] do
    sh "#{command :solution} < #{packed_input} > #{packed_output}"
    sh "bash -c '#{command :check} #{packed_input} #{packed_output} <(cat #{outputs.join(' ')})'"
  end

  task default: packed_output
end

task :clean do
  sh 'rm -rf *.a *.class *.exe input output answer out ans aux samples tests'
  if /darwin/ =~ RUBY_PLATFORM
    sh 'find . -perm +u+x -type f -delete'
  else
    sh 'find . -executable -delete'
  end
end
