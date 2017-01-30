<?php
require_once __DIR__ . '/../vendor/autoload.php';
require_once __DIR__ . '/../config/config.php';

$app = new Silex\Application();

$app['config'] = $config;

$app->register(new Silex\Provider\TwigServiceProvider(), [
	'twig.path' => __DIR__ . '/../view',
]);

$app->extend('twig', function($twig, $app) {
    return $twig;
});

// index
$app->get('/', function () use ($app) {
    return $app->redirect('https://fosdem.org/schedule/streaming/');
});

// watch
$app->get('/watch/{room}', function ($room) use ($app) {
	if (!isset($app['config']['rooms'][$room])) {
		throw new \Exception('Unknown room');
	}

	return $app['twig']->render('watch.twig', [
		'room' => $room,
		'room_name' => $app['config']['rooms'][$room],
	]);
});

$app->run();
