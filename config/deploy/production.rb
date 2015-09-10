# set :deploy_to, '/var/www/staging/drupal_api'

# set a branch for this release
# set :branch, 'develop'

SSHKit.config.command_map[:composer] = "#{shared_path.join("composer.phar")}"
SSHKit.config.command_map[:drush] = "#{shared_path.join("vendor/bin/drush")}"

server '192.168.10.10',
user: 'vagrant'
# roles: %w{'192.168.10.10'},