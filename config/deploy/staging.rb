role :app, %w{54.255.187.149}

set :deploy_to, '/home/ubuntu/www/webApp/staging'

set :settings_path, "#{fetch(:deploy_to)}/shared/sites/default"

# set a branch for this release
set :branch, 'develop'

set :app_environment, 'staging'

# SSHKit.config.command_map[:composer] = "#{shared_path.join("composer.phar")}"
# SSHKit.config.command_map[:drush] = "#{shared_path.join("vendor/bin/drush")}"

set :file_permissions_paths, ["sites/default/files"]
set :file_permissions_users, ["ubuntu"]
set :file_permissions_chmod_mode, "0777"

server '54.255.187.149',
user: 'ubuntu',
roles: %w{'54.255.187.149'}