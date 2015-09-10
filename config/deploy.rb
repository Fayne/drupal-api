# config valid only for current version of Capistrano
lock '3.4.0'

set :application, 'wpp_api'
set :repo_url, 'ssh://git@stash.mobilenowstaging.com:7999/wpp/web.git'

# Default branch is :master
ask :branch, `git rev-parse --abbrev-ref HEAD`.chomp

# Default deploy_to directory is /var/www/my_app_name
set :deploy_to, '/home/ubuntu/www/webApp/public'

# Default value for :scm is :git
# set :scm, :git

# Default value for :format is :pretty
# set :format, :pretty

# Default value for :log_level is :debug
set :log_level, :debug

# Default value for :pty is false
set :pty, true

set :app_path,        "./"

# Default value for :linked_files is []
set :linked_files, fetch(:linked_files, []).push('sites/default/settings.php')

# Default value for linked_dirs is []
set :linked_dirs, fetch(:linked_dirs, []).push('sites/default/files', 'sites/default/private')

# Default value for default_env is {}
# set :default_env, { path: "/opt/ruby/bin:$PATH" }

# Default value for keep_releases is 5
# set :keep_releases, 5

namespace :deploy do

  task :upload_setting do
    on roles(:app) do
      execute "mkdir", "-p #{fetch(:settings_path)}"
      execute "rm", "-f #{fetch(:settings_path)}/setting*.php"
      upload! "sites/default/settings.#{fetch(:app_environment)}.php", fetch(:settings_path), :recursive => true
    end
  end

  before "deploy:check:linked_files", "deploy:upload_setting"

  task :rename_setting do
    on roles(:app) do
      execute "mv", "#{fetch(:settings_path)}/settings.#{fetch(:app_environment)}.php #{fetch(:settings_path)}/settings.php"
      execute "chmod", "444 #{fetch(:settings_path)}/settings.php"
    end
  end

  after :upload_setting, :rename_setting

  # before :updated, deploy:set_permissions:acl

end
