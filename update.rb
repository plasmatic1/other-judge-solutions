# Update codeforces submissions
puts "Getting codeforces submissions..."
%x(cd codeforces)
puts "Main account (Plasmatic)"
%x(get-submissions -h Plasmatic)
puts "\nAlt account (zey_zey_chen)"
%x(get-submissions -h zey_zey_chen)
puts
%x(cd ..)


